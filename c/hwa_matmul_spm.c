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
#define FACTOR				0
#define B_START				1

#elif(NBANKS==5)

#define BRAM_BASE_READ 		0xF00B4000
#define FACTOR				1
#define B_START				2

#elif(NBANKS==9)

#define BRAM_BASE_READ 		0xF00B8000
#define FACTOR				2
#define B_START				4

#else

#define BRAM_BASE_READ 		0xF00B0000
#define FACTOR				0
#define B_START				1

#endif

int main(void);
int matmul_main(mat_type mat_a[DIM][DIM],
				mat_type mat_b[DIM][DIM],
				mat_type sw_result[DIM][DIM]) __attribute__ ((noinline));
int matmul_main_wcet(void) __attribute__((noinline));

struct matmul_matrix {
	mat_type mat_a[DIM][DIM];
	mat_type mat_b[DIM][DIM];
	mat_type hw_result[DIM][DIM];
};

volatile _SPM struct matmul_matrix *spm_matrix = (volatile _SPM struct matmul_matrix *) SPM_BASE;
volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;

int _Pragma("entrypoint") matmul_main_wcet()
{

#if(WRITE)

	#if(NBANKS==3)

		write_array_spm(spm_matrix->mat_a, DIM, DIM, FACTOR, 0, 1);

	#else

		write_array_spm(spm_matrix->mat_a, DIM, DIM, FACTOR, 0, 2);

	#endif

	write_array_spm(spm_matrix->mat_b, DIM, DIM, FACTOR, B_START, 1);

#endif

#if(COMP)

	*hls_ptr = 1;
	_Pragma("loopbound min 1 max 1")
	while((*hls_ptr) != 1){
	}	

#endif		

#if(READ)

	read_array_spm(spm_matrix->hw_result, DIM, DIM, 1, BRAM_BASE_READ);

#endif

	return 0;

}

unsigned long long start_compute, stop_compute, return_compute = 0;
unsigned long long start_write, stop_write, return_write = 0;
unsigned long long start_read, stop_read, return_read = 0;	

int __attribute__ ((noinline)) matmul_main(mat_type mat_a[DIM][DIM],
				mat_type mat_b[DIM][DIM],
				mat_type sw_result[DIM][DIM])
{
	
#if(WRITE)

	// Write to BRAM	

	start_write = get_cpu_cycles();

	#if(NBANKS==3)

		write_array_spm(spm_matrix->mat_a, DIM, DIM, FACTOR, 0, 1);

	#else

		write_array_spm(spm_matrix->mat_a, DIM, DIM, FACTOR, 0, 2);

	#endif

	write_array_spm(spm_matrix->mat_b, DIM, DIM, FACTOR, B_START, 1);

	stop_write = get_cpu_cycles();
	return_write = stop_write-start_write-CYCLE_CALIBRATION;

#endif	

	// Start HLS module

#if(COMP)

	start_compute = get_cpu_cycles();

	*hls_ptr = 1;

	// Poll status of HLS module

	while((*hls_ptr) != 1);

	stop_compute = get_cpu_cycles();
	return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;

#endif		

	// Read back the data

#if(READ)

	start_read = get_cpu_cycles();

	read_array_spm(spm_matrix->hw_result, DIM, DIM, 1, BRAM_BASE_READ);

	stop_read = get_cpu_cycles();
	return_read = stop_read-start_read-CYCLE_CALIBRATION;

#endif

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

	// Compute expected results

	matmul_expected(mat_a, mat_b, sw_result);

#if(WCET)

	return matmul_main_wcet();

#else

	matmul_main(mat_a, mat_b, sw_result);

	print_benchmark(return_compute, return_write, return_read);	

	return compare_arrays_spm(&spm_matrix->hw_result, sw_result);

#endif
}