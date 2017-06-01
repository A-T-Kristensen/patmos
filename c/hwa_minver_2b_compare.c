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

int minver_main(mat_type minver_hw_i[DIM][DIM],
				mat_type minver_sw_i[DIM][DIM]);

int minver_main_wcet(mat_type minver_hw_i[DIM][DIM]) __attribute__((noinline));
int main(void);

int _Pragma("entrypoint") minver_main_wcet(mat_type minver_hw_i[DIM][DIM])
{

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;

#if(NBANKS>1)

	write_array(minver_hw_i, DIM, DIM, NBANKS, 0, bank_ptr_array, 2, 0);

#else

	write_array(minver_hw_i, DIM, DIM, NBANKS, 0, bank_ptr_array, 1, 0);

#endif

	*hls_ptr = 1;

#if(NBANKS>1)

	read_array(minver_hw_i, DIM, DIM, NBANKS, 0, bank_ptr_array, 2, 0);

#else

	read_array(minver_hw_i, DIM, DIM, NBANKS, 0, bank_ptr_array, 1, 0);

#endif

	return 0;
}

int minver_main(mat_type minver_hw_i[DIM][DIM],
				mat_type minver_sw_i[DIM][DIM])
{

	int err_cnt = 0;
	mat_type eps = 1.0e-6;

	unsigned long long start_compute, stop_compute, return_compute = 0;
	unsigned long long start_transfer, stop_transfer, return_transfer = 0;

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;

	printf("Benchmarking \n");

	// Compute expected results

	minver_minver(minver_sw_i, DIM, eps);

	// Run accelerator

	start_transfer = get_cpu_cycles();

#if(NBANKS>1)

	write_array(minver_hw_i, DIM, DIM, NBANKS, 0, bank_ptr_array, 2, 0);

#else

	write_array(minver_hw_i, DIM, DIM, NBANKS, 0, bank_ptr_array, 1, 0);

#endif

	// Poll status of HLS module
	*hls_ptr = 1;
	
	while((*hls_ptr) != 1);

#if(NBANKS>1)

	read_array(minver_hw_i, DIM, DIM, NBANKS, 0, bank_ptr_array, 2, 0);

#else

	read_array(minver_hw_i, DIM, DIM, NBANKS, 0, bank_ptr_array, 1, 0);

#endif

	stop_transfer = get_cpu_cycles();
	return_transfer += stop_transfer-start_transfer-CYCLE_CALIBRATION;

	err_cnt = compare_arrays(minver_hw_i, minver_sw_i);

	print_benchmark(return_compute, return_transfer);

	return err_cnt;
}

int main(void)
{
	mat_type minver_hw_i[DIM][DIM];
	mat_type minver_sw_i[DIM][DIM];	

	set_minver(minver_hw_i);
	set_minver(minver_sw_i);

#if(WCET)

	return minver_main_wcet(minver_hw_i);

#else

	return minver_main(minver_hw_i, minver_sw_i);

#endif
}