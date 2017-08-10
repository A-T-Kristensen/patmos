/*
	This c file contains the main benchmark program
	for matrix inversion.

	It is based on the "minver" benchmark from the TACLeBench
	benchmark suite (author Sung-Soo Lim).

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License

	This program is derived from the SNU-RT Benchmark Suite for Worst
	Case Timing Analysis by Sung-Soo Lim

	Original source: Turbo C Programming for Engineering by Hyun Soo Ahn

 */

#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"
#include "libminver/minver_init.h"
#include "libminver/minver.h"

struct minver_matrix {
	mat_type hw_result[DIM][DIM];
};

volatile _SPM struct minver_matrix *spm_matrix = (volatile _SPM struct minver_matrix *) SPM_BASE;

int minver_main(mat_type sw_result[DIM][DIM]);
int minver_main_wcet(void) __attribute__((noinline));
int main(void);

int _Pragma("entrypoint") minver_main_wcet()
{

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

#if(NBANKS>1)

	write_array_spm(&spm_matrix->hw_result, DIM, DIM,
					NBANKS, 0, bank_ptr_array, 2);

#else

	write_array_spm(&spm_matrix->hw_result, DIM, DIM,
					1, 0, bank_ptr_array, 1);

#endif

	*hls_ptr = 1;
	*hls_ptr;

#if(NBANKS>1)

	read_array_spm(&spm_matrix->hw_result, DIM, DIM,
				   NBANKS, 0, bank_ptr_array, 2);

#else

	read_array_spm(&spm_matrix->hw_result, DIM, DIM,
				   NBANKS, 0, bank_ptr_array, 1);

#endif

	return 0;
}


int minver_main(mat_type sw_result[DIM][DIM])
{

	int err_cnt = 0;
	mat_type eps = 1.0e-6;

	unsigned long long start_compute, stop_compute, return_compute = 0;
	unsigned long long start_write, stop_write, return_write = 0;
	unsigned long long start_read, stop_read, return_read = 0;	

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	printf("Benchmarking \n");

	// Compute expected results

	minver_minver(sw_result, DIM, eps);

	// Run accelerator

	start_write = get_cpu_cycles();

#if(NBANKS>1)

	write_array_spm(&spm_matrix->hw_result, DIM, DIM,
					NBANKS, 0, bank_ptr_array, 2);

#else

	write_array_spm(&spm_matrix->hw_result, DIM, DIM,
					1, 0, bank_ptr_array, 1);

#endif

	stop_write = get_cpu_cycles();
	return_write = stop_write-start_write-CYCLE_CALIBRATION;

	// Poll status of HLS module

	start_compute = get_cpu_cycles();

	*hls_ptr = 1;

	while((*hls_ptr) != 1);

	stop_compute = get_cpu_cycles();
	return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;

	start_read = get_cpu_cycles();

#if(NBANKS>1)

	read_array_spm(&spm_matrix->hw_result, DIM, DIM,
				   NBANKS, 0, bank_ptr_array, 2);

#else

	read_array_spm(&spm_matrix->hw_result, DIM, DIM,
				   NBANKS, 0, bank_ptr_array, 1);

#endif

	stop_read = get_cpu_cycles();
	return_read = stop_read-start_read-CYCLE_CALIBRATION;

	err_cnt = compare_arrays_spm(&spm_matrix->hw_result,
								 sw_result);

	print_benchmark(return_compute, return_write, return_read);

	return err_cnt;
}

int main(void)
{
	mat_type sw_result[DIM][DIM];

	set_minver_spm(&spm_matrix->hw_result);
	set_minver(sw_result);

#if(WCET)

	return minver_main_wcet();

#else

	return minver_main(sw_result);

#endif

}
