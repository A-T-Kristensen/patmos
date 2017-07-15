/*
	This is a minimal C program executed on the FPGA version of Patmos.
	An embedded test of a vivado HLS HwA module: Matrix multiplication on
	an array of dimension DIM partitionen into NBANKS memory banks.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License
 */

#include "libhwa/hwa_lib.h"
#include "libmatmul/matmul_hwa.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

#if(NBANKS==3)

#define BRAM_BASE_READ 		0xF00B2000

#elif(NBANKS==5)

#define BRAM_BASE_READ 		0xF00B4000

#elif(NBANKS==9)

#define BRAM_BASE_READ 		0xF00B8000

#else

#define BRAM_BASE_READ 		0xF00B0000

#endif

int matmul_main(mat_type mat_a[DIM][DIM],
				mat_type mat_b[DIM][DIM],
				mat_type sw_result[DIM][DIM],
				mat_type hw_result[DIM][DIM])
{

	int err_cnt = 0;

	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) BRAM_BASE;
	volatile _IODEV mat_type *bram_ptr_write = (volatile _IODEV mat_type *) BRAM_BASE;
	volatile _IODEV mat_type *bram_ptr_read = (volatile _IODEV mat_type *) BRAM_BASE_READ;
	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

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
		*(bram_ptr_write + 1) = *(&mat_a[0][0] + i);
	}

	// Set up BRAM for B

	start_bank = 2; // For NBANKS == 5
	wr_dim = 1;

	*(bram_ptr) = (array_vect << 30) | (wr_dim << 28) | (M << 18)
				  | (N << 8) | (factor << 4) | start_bank;

	// Write data to BRAM

	for(i = 0; i < M*N; i++) {
		*(bram_ptr_write + 1) = *(&mat_b[0][0] + i);
	}

	// Start HLS module

	*hls_ptr = 1;

	// Poll status of HLS module

	while((*hls_ptr) != 1);

	for(i = 0; i < M*N; i++) {
		*(&hw_result[0][0] + i) = *(bram_ptr_read + i);
	}

	int j;

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
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
