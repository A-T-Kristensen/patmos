/*
	This is a minimal C program executed on the FPGA version of Patmos.
	An embedded test of a vivado HLS HwA module: Matrix multiplication on
	an array of dimension DIM partitionen into NBANKS memory banks.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License
 */

#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.

#define ADDR_BITS 			16

#define LED_RUN_LENGTH 		2
#define LED_ROUNDS			10

#define BRAM_BASE 			0xF00B0000
#define BRAM_BASE_2 		0xF00B1000
#define BRAM_BASE_READ 		0xF00B2000
#define HWA_CTRL_BASE 		0xF00C0000
#define LED_BASE 			0xF0090000

#define ROWS 	4
#define COLS	4
#define DIM 	4
#define SIZE	16
#define NBANKS 	3
typedef float mat_type; // Float does not work for simulation

#include <stdio.h>
#include <stdlib.h>

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

	if(!err_cnt) {
		puts("Results correct");
	}

	else {
		puts("Results incorrect");
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
	volatile _IODEV mat_type *bram_ptr_2 = (volatile _IODEV mat_type *) BRAM_BASE_2;

	volatile _IODEV mat_type *bram_ptr_read = (volatile _IODEV mat_type *) BRAM_BASE_READ;

	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;

	int i;

	// Compute expected results

	matmul_expected(mat_a, mat_b, sw_result);

	// Division factor, a and b shares most banks

	int wr_dim = 1;	
	int factor = 1; // 1 means no division
	int array_vect =  0; // Array
	int M = DIM;
	int N = DIM;
	int start_bank = 0;	

	// Set up BRAM
	*(bram_ptr) =  (array_vect << 30) | (wr_dim << 28) | (M << 18) 
					| (N << 8) | (factor << 4) | start_bank;

	// Write data to BRAM 
	
	for(i = 0; i < M*N; i++)
	{
		*(bram_ptr + 1) = *(&mat_a[0][0] + i);
	}

	// Set up BRAM for B	

	start_bank = 1;	
	wr_dim = 1;	

	*(bram_ptr) =  (array_vect << 30) | (wr_dim << 28) | (M << 18) 
					| (N << 8) | (factor << 4) | start_bank;

	// Write data to BRAM
	
	for(i = 0; i < M*N; i++)
	{
		*(bram_ptr + 1) = *(&mat_b[0][0] + i);
	}	

	// Start HLS module

	*hls_ptr = 1;

	// Poll status of HLS module

	while((*hls_ptr) != 1);

/*	for(i = 0; i < M*N; i++)
	{
		*(&hw_result[0][0] + i) = *(bram_ptr_read + i);
	}
*/

	for(i = 0; i < M*N; i++)
	{
		*(&hw_result[0][0] + i) = *(bram_ptr_read + i);
	}

	for(i = 0; i < M*N*3; i++)
	{
		printf("%f ", *(bram_ptr_2 + i));
	}	

	printf("\n");

	int j;

	for(i = 0; i < DIM; i++){
		for(j = 0; j < DIM; j++){
			printf("%f ", mat_a[i][j]);
		}
		printf("\n");
	}

	printf("\n");


	for(i = 0; i < DIM; i++){
		for(j = 0; j < DIM; j++){
			printf("%f ", mat_b[i][j]);
		}
		printf("\n");
	}

	printf("\n");


	for(i = 0; i < DIM; i++){
		for(j = 0; j < DIM; j++){
			printf("%f ", hw_result[i][j]);
		}
		printf("\n");
	}

	err_cnt = compare_arrays(hw_result, sw_result);

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
