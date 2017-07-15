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

int main(void);
int matmul_main(mat_type mat_a[DIM][DIM],
				mat_type mat_b[DIM][DIM],
				mat_type sw_result[DIM][DIM],
				mat_type hw_result[DIM][DIM]
			   ) ;
int matmul_main_wcet(mat_type mat_a[DIM][DIM],
					 mat_type mat_b[DIM][DIM],
					 mat_type hw_result[DIM][DIM]) __attribute__((noinline));

int _Pragma("entrypoint") matmul_main_wcet(mat_type mat_a[DIM][DIM],
		mat_type mat_b[DIM][DIM],
		mat_type hw_result[DIM][DIM])
{

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);
	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;

	// Division factor, a and b shares most banks

	int factor = (int) floor(NBANKS/2);

	// Write to BRAM
	write_vector(mat_a, DIM*DIM, factor, 0, bank_ptr_array);
	write_vector(mat_b, DIM*DIM, factor, factor, bank_ptr_array);

	*(hls_ptr + 1) = DIM;
	*hls_ptr = 1;
	*hls_ptr;

	read_vector(hw_result, DIM*DIM, 1, NBANKS-1, bank_ptr_array);

	return 0;
}

int matmul_main(mat_type mat_a[DIM][DIM],
				mat_type mat_b[DIM][DIM],
				mat_type sw_result[DIM][DIM],
				mat_type hw_result[DIM][DIM])
{

	int err_cnt = 0;
	int i, j;

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	unsigned long long start_compute, stop_compute, return_compute = 0;
	unsigned long long start_transfer, stop_transfer, return_transfer = 0;

	mat_type hw_result_vec[DIM*DIM];

	int sw_sum = 0, hw_sum = 0;

	// Division factor, a and b shares most banks

	int factor = (int) floor(NBANKS/2);

	printf("Benchmarking \n");

	// Compute expected results

	matmul_expected(mat_a, mat_b, sw_result);

	// Write to BRAM

	start_transfer = get_cpu_cycles();

#if(NBANKS==3)

	write_vector(mat_a, DIM*DIM, factor, 0, bank_ptr_array);

#else

	write_vector(mat_a, DIM*DIM, factor, 0, bank_ptr_array);

#endif

	write_vector(mat_b, DIM*DIM, factor, factor, bank_ptr_array);

	stop_transfer = get_cpu_cycles();
	return_transfer = stop_transfer-start_transfer-CYCLE_CALIBRATION;

	// Start HLS module

	start_compute = get_cpu_cycles();

	*(hls_ptr + 1) = DIM;
	*hls_ptr = 1;

	// Poll status of HLS module

	while((*hls_ptr) != 1);

	stop_compute = get_cpu_cycles();
	return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;

	// Read back the data

	start_transfer = get_cpu_cycles();

	read_vector(hw_result_vec, DIM*DIM, 1, NBANKS-1, bank_ptr_array);

	stop_transfer = get_cpu_cycles();
	return_transfer += stop_transfer-start_transfer-CYCLE_CALIBRATION;


	for(i = 0; i < DIM*DIM; i++) {
		hw_sum+= (int) hw_result_vec[i];
	}

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			sw_sum+= (int) sw_result[i][j];
		}
	}

	print_benchmark(return_compute, return_transfer);

	return (int) sw_sum - hw_sum;
}

int main()
{

	mat_type mat_a[DIM][DIM], mat_b[DIM][DIM];
	mat_type sw_result[DIM][DIM], hw_result[DIM][DIM];

	// Initialize matrices

	matmul_init(mat_a, mat_b, sw_result);

#if(WCET)

	return matmul_main_wcet(mat_a, mat_b, hw_result);

#else

	return matmul_main(mat_a, mat_b, sw_result, hw_result);

#endif
}
