/*
 *	This is a minimal C program executed on the FPGA version of Patmos.
 *	An embedded test of a vivado hls module: Matrix multiplication 
 *	on an array of dimension DIM partitioned into NBANKS memory banks-
 *
 *	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
 *	Copyright: DTU, BSD License
 */

#include "libhwa/hwa_lib.h"
#include "libmatmul/matmul_hwa.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

struct matrix {
    mat_type mat_a[DIM][DIM];
    mat_type mat_b[DIM][DIM];
    mat_type hw_result[DIM][DIM]; 
    mat_type sw_result[DIM][DIM]; 
};

volatile _UNCACHED struct matrix *spm_matrix;

int main() 
{
	int i, j, k;
	int err_cnt = 0;

	volatile _IODEV mat_type** bank_ptr_array = (volatile _IODEV mat_type**) bank_ptrs(NBANKS);

	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;    

	unsigned long long start_cycle, stop_cycle, calibration;	
	unsigned long long return_cycles = 0;		

	int factor = (int) floor(NBANKS/2); // Division factor, a and b shares most banks
	int n = DIM; // the # columns
	int m = DIM; // the # rows
	int a_bank0 = 0; // Start bank
	int b_bank0 = factor;	

	matmul_init_uncached(&spm_matrix->mat_a, &spm_matrix->mat_b, &spm_matrix->sw_result);
	matmul_expected_uncached(&spm_matrix->mat_a, &spm_matrix->mat_b, &spm_matrix->sw_result);

	printf("Benchmarking \n");	

   // Write to BRAM

	start_cycle = get_cpu_cycles();

   // Bank 1

	if(NBANKS == 3) {
		write_array_uncached(&spm_matrix->mat_a, n, m, factor, a_bank0, bank_ptr_array, 1);
	}
	else {
		write_array_uncached(&spm_matrix->mat_a, n, m, factor, a_bank0, bank_ptr_array, 2);		
	}

	write_array_uncached(&spm_matrix->mat_b, n, m, factor, b_bank0, bank_ptr_array, 1);	

    // Start HLS module

	printf("HWA Running \n");    
	
	*hls_ptr = 1;

	// Poll status of HLS module
    
    while((*hls_ptr) != 1);

    // Read back the data    

    for(i = 0; i < DIM*DIM; i++)
    {
        *((&(spm_matrix->hw_result[0][0])) + i)= *(bank_ptr_array[NBANKS-1]  + i);
    }    
	

	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-CYCLE_CALIBRATION;

	// Check results
	
	check_matmul_uncached(&spm_matrix->hw_result, &spm_matrix->sw_result);

	printf("#Cycles = %llu \n", return_cycles);	

	return 0;
}
