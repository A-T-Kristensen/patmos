/*
 *	This is a minimal C program executed on the FPGA version of Patmos.
 *	An embedded test of a vivado hls module: Matrix multiplication on 
 *	an array of dimension DIM partitioned into NBANKS memory banks
 *
 *	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
 *	Copyright: DTU, BSD License
 */

#include "hwa_lib.h"

struct matrix {
    mat_type mat_a[DIM][DIM];
    mat_type mat_b[DIM][DIM];
    mat_type hw_result[DIM][DIM]; 
    mat_type sw_result[DIM][DIM]; 
};

volatile _SPM struct matrix *spm_matrix = (volatile _SPM struct matrix *) SPM_BASE;

int main() 
{
	int i, j, k, err_cnt = 0;

	volatile _IODEV mat_type** bank_ptr_array = (volatile _IODEV mat_type**) bank_ptrs(NBANKS);
	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;    

	unsigned long long start_cycle, stop_cycle, return_cycles;	

	int factor = (int) floor(NBANKS/2); // Division factor, a and b shares most banks
	int n = DIM; // the # columns
	int m = DIM; // the # rows
	int a_bank0 = 0; // Start bank
	int b_bank0 = factor;		

	printf("HWA Running \n");	

	// Initialize matrices

	matmul_init_spm(&spm_matrix->mat_a, &spm_matrix->mat_b, &spm_matrix->sw_result);
	matmul_expected_spm(&spm_matrix->mat_a, &spm_matrix->mat_b, &spm_matrix->sw_result);

   // Write to BRAM

	start_cycle = get_cpu_cycles();

   // Bank 1

	if(NBANKS == 3) {
		write_array_spm(&spm_matrix->mat_a, n, m, factor, a_bank0, bank_ptr_array, 1);
	}
	else {
		write_array_spm(&spm_matrix->mat_a, n, m, factor, a_bank0, bank_ptr_array, 2);		
	}

	write_array_spm(&spm_matrix->mat_b, n, m, factor, b_bank0, bank_ptr_array, 1);	

    // Start HLS module
	
	*hls_ptr = 1;

	// Poll status of HLS module
    
    while((*hls_ptr) != 1);

    // Read back the data    

    for(i = 0; i < DIM*DIM; i++)
    {
        *((&(spm_matrix->hw_result[0][0])) + i) = *(bank_ptr_array[NBANKS-1] + i);
    }    
	
	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-CYCLE_CALIBRATION;
	printf("#Cycles = %llu \n", return_cycles);

	// Check results

    puts("Checking results");	

	check_matmul_spm(&spm_matrix->hw_result, &spm_matrix->sw_result);
	
	return 0;
}
