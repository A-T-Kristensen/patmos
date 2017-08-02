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

#define BRAM0	0xF00B0000
#define BRAM1	0xF00B1000
#define BRAM2	0xF00B2000
#define BRAM3	0xF00B3000
#define BRAM4	0xF00B4000
#define BRAM5	0xF00B5000
#define BRAM6	0xF00B6000
#define BRAM7	0xF00B7000

volatile _IODEV mat_type *bram_ptr_read0 = (volatile _IODEV mat_type *) BRAM0;
volatile _IODEV mat_type *bram_ptr_read1 = (volatile _IODEV mat_type *) BRAM1;
volatile _IODEV mat_type *bram_ptr_read2 = (volatile _IODEV mat_type *) BRAM2;
volatile _IODEV mat_type *bram_ptr_read3 = (volatile _IODEV mat_type *) BRAM3;
volatile _IODEV mat_type *bram_ptr_read4 = (volatile _IODEV mat_type *) BRAM4;
volatile _IODEV mat_type *bram_ptr_read5 = (volatile _IODEV mat_type *) BRAM5;
volatile _IODEV mat_type *bram_ptr_read6 = (volatile _IODEV mat_type *) BRAM6;
volatile _IODEV mat_type *bram_ptr_read7 = (volatile _IODEV mat_type *) BRAM7;


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
//	int factor = 0; // 0 means no division
	//int factor = 1; // 1 means 2 banks
	int factor = 2; // 2 means 4 banks

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

//	start_bank = 2; // For NBANKS == 5
	start_bank = 4; // For NBANKS == 9

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

/*	int j;

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			printf("%d ", mat_a[i][j]);
		}
		printf("\n");
	}

	printf("\n");


	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			printf("%d ", mat_b[i][j]);
		}
		printf("\n");
	}		

	printf("\n");


	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			printf("%d ", hw_result[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			printf("%d ", sw_result[i][j]);
		}
		printf("\n");
	}	

	printf("\n");		


	for(i = 0; i < DIM*DIM; i++) {
		printf("%d ", *(bram_ptr_read0 + i));
	}		

	printf("\n");

	for(i = 0; i < DIM*DIM; i++) {
		printf("%d ", *(bram_ptr_read1 + i));
	}		

	printf("\n");

	for(i = 0; i < DIM*DIM; i++) {
		printf("%d ", *(bram_ptr_read2 + i));
	}		

	printf("\n");

	for(i = 0; i < DIM*DIM; i++) {
		printf("%d ", *(bram_ptr_read3 + i));
	}		

	printf("\n");

	for(i = 0; i < DIM*DIM; i++) {
		printf("%d ", *(bram_ptr_read4 + i));
	}		

	printf("\n");		

	for(i = 0; i < DIM*DIM; i++) {
		printf("%d ", *(bram_ptr_read5 + i));
	}		

	printf("\n");	

	for(i = 0; i < DIM*DIM; i++) {
		printf("%d ", *(bram_ptr_read6 + i));
	}		

	printf("\n");	

	for(i = 0; i < DIM*DIM; i++) {
		printf("%d ", *(bram_ptr_read7 + i));
	}		

	printf("\n");			
*/

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
