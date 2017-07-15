/*
	This is a minimal C program executed on the FPGA version of Patmos.
	An embedded test of a vivado HLS HwA module: Matrix multiplication on
	an array of dimension DIM partitionen into NBANKS memory banks.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License
 */


#include "include/patio.h"
#include "include/bootable.h"
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.


#define ADDR_BITS 			16

#define LED_RUN_LENGTH 		2
#define LED_ROUNDS			10

#define BRAM_BASE 			0xF00B0000
#define BRAM_BASE_READ 		0xF00B4000
#define HWA_CTRL_BASE 		0xF00C0000
#define LED_BASE 			0xF0090000

#define ROWS 	4
#define COLS	4
#define DIM 	4
#define SIZE	16
#define NBANKS	5
typedef int mat_type; // Float does not work for simulation

void matmul_init(mat_type mat_a[DIM][DIM],
				 mat_type mat_b[DIM][DIM],
				 mat_type sw_result[DIM][DIM])
{

	int i, j;

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {

			mat_a[i][j] = i + j + 1;
			mat_b[i][j] = i + j + 1 + DIM;
			sw_result[i][j] = 0;
		}
	}
}

void matmul_expected(mat_type mat_a[DIM][DIM],
					 mat_type mat_b[DIM][DIM],
					 mat_type sw_result[DIM][DIM])
{
	int i, j, k;

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			for(k = 0; k < DIM; k++) {
				sw_result[i][j] += mat_a[i][k] * mat_b[k][j];
			}
		}
	}
}

void led_blink(int err_cnt)
{

	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) LED_BASE;
	int i, j;

	if(!err_cnt) {
		for(i = 0; i < LED_ROUNDS; i++) {
			for(i=LED_RUN_LENGTH; i!=0; --i)
				for(j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 3;

			for(i=LED_RUN_LENGTH; i!=0; --i)
				for(j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;

			for(i=LED_RUN_LENGTH; i!=0; --i)
				for(j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 15;

			for(i=LED_RUN_LENGTH; i!=0; --i)
				for(j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;

			for(i=LED_RUN_LENGTH; i!=0; --i)
				for(j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 63;

			for(i=LED_RUN_LENGTH; i!=0; --i)
				for(j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
		}
	}

	else {
		for(i = 0; i < LED_ROUNDS; i++) {
			for(i=LED_RUN_LENGTH; i!=0; --i)
				for(j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;

			for(i=LED_RUN_LENGTH; i!=0; --i)
				for(j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 7;
		}
	}
}

int compare_arrays(mat_type hw_result[ROWS][COLS],
				   mat_type sw_result[ROWS][COLS])
{

	int i, j, err_cnt = 0;

	for(i = 0; i < ROWS; i++) {
		for(j = 0; j < COLS; j++) {
			if(hw_result[i][j] != sw_result[i][j]) {
				err_cnt++;
			}
		}
	}

	return err_cnt;
}


int matmul_main(mat_type mat_a[DIM][DIM],
				mat_type mat_b[DIM][DIM],
				mat_type sw_result[DIM][DIM],
				mat_type hw_result[DIM][DIM])
{

	int err_cnt = 0;

	volatile _IODEV mat_type *bram_ptr = (volatile _IODEV mat_type *) BRAM_BASE;
	volatile _IODEV mat_type *bram_ptr_read = (volatile _IODEV mat_type *) BRAM_BASE_READ;

	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;

	int i;

	// Compute expected results

	matmul_expected(mat_a, mat_b, sw_result);

	// Division factor, a and b shares most banks

	int wr_dim = 2;
	int factor = 2; // 1 means no division
	int array_vect =  0; // Array
	int M = DIM;
	int N = DIM;
	int start_bank = 0;

	// Set up BRAM
	*(bram_ptr) = (array_vect << 30) | (wr_dim << 28) | (M << 18)
				  | (N << 8) | (factor << 4) | start_bank;

	// Write data to BRAM

	for(i = 0; i < M*N; i++) {
		*(bram_ptr + 1) = *(&mat_a[0][0] + i);
	}

	// Set up BRAM for B

	start_bank = 2;
	wr_dim = 1;

	*(bram_ptr) = (array_vect << 30) | (wr_dim << 28) | (M << 18)
				  | (N << 8) | (factor << 4) | start_bank;

	// Write data to BRAM

	for(i = 0; i < M*N; i++) {
		*(bram_ptr + 1) = *(&mat_b[0][0] + i);
	}

	// Start HLS module

	*hls_ptr = 1;

	// Poll status of HLS module

	while((*hls_ptr) != 1);

	for(i = 0; i < M*N; i++) {
		*(&hw_result[0][0] + i) = *(bram_ptr_read + i);
	}

	err_cnt = compare_arrays(hw_result, sw_result);

	led_blink(err_cnt);

	return err_cnt;
}

int main()
{

	mat_type mat_a[DIM][DIM], mat_b[DIM][DIM];
	mat_type sw_result[DIM][DIM], hw_result[DIM][DIM];

	// Initialize matrices

	matmul_init(mat_a, mat_b, sw_result);
	matmul_main(mat_a, mat_b, sw_result, hw_result);

	return 0;
}
