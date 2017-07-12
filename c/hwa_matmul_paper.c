/*
	This is a minimal C program executed on the FPGA version of Patmos.
	An embedded test of a vivado hls module: Matrix multiplication on
	an array of dimension DIM partitioned into NBANKS memory banks.

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

int main(void);
int matmul_main_wcet(void) __attribute__((noinline));

struct matmul_matrix {
	mat_type mat_a[DIM][DIM];
	mat_type mat_b[DIM][DIM];
	mat_type hw_result[DIM][DIM];
};

volatile _SPM struct matmul_matrix *spm_matrix = (volatile _SPM struct matmul_matrix *) SPM_BASE;

int _Pragma("entrypoint") matmul_main_wcet()
{

	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;

	// Division factor, a and b shares most banks
	int factor = (int) floor(NBANKS/2);

	// Write to BRAM

#if(NBANKS==3)

	write_array_spm(spm_matrix->mat_a, DIM, DIM,
					factor, 0, 1);

#else

	write_array_spm(spm_matrix->mat_a, DIM, DIM,
					factor, 0, 2);

#endif

	write_array_spm(spm_matrix->mat_b, DIM, DIM,
					factor, factor, 1);

	*hls_ptr = 1;
	*hls_ptr;	

	// Read back
	read_array_spm(spm_matrix->hw_result, DIM, DIM,
				   1, BRAM_BASE_READ);

	return 0;
}

int main()
{

	mat_type mat_a[DIM][DIM];
	mat_type mat_b[DIM][DIM];
	mat_type sw_result[DIM][DIM];	

	// Initialize matrices

	matmul_init(mat_a, mat_b, sw_result);

	matmul_init_spm(&spm_matrix->mat_a,
					&spm_matrix->mat_b,
					&spm_matrix->hw_result);

#if(WCET)

	return matmul_main_wcet();

#else

	return 0;

#endif
}