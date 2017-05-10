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

int main(void);

struct matmul_matrix {
    mat_type mat_a[DIM][DIM];
    mat_type mat_b[DIM][DIM];
    mat_type hw_result[DIM][DIM]; 
    mat_type sw_result[DIM][DIM]; 
};

volatile _SPM struct matmul_matrix *spm_matrix = (volatile _SPM struct matmul_matrix *) SPM_BASE;

int main(){

	int i, j, k, err_cnt = 0;

    volatile _IODEV mat_type *bank_ptr_array[NBANKS];
    bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;    

    unsigned long long start_compute, stop_compute, return_compute;  
    unsigned long long start_transfer, stop_transfer, return_transfer;    

    // Division factor, a and b shares most banks
	int factor = (int) floor(NBANKS/2); 

	printf("Benchmarking \n");

	// Initialize matrices

	matmul_init_spm(&spm_matrix->mat_a, 
                    &spm_matrix->mat_b, 
                    &spm_matrix->sw_result);

	// Compute expected results

	matmul_expected_spm(&spm_matrix->mat_a, 
                        &spm_matrix->mat_b, 
                        &spm_matrix->sw_result);

   // Write to BRAM

    start_transfer = get_cpu_cycles();

    #if(NBANKS==3)

	write_array_spm(&spm_matrix->mat_a, DIM, DIM, 
                    factor, 0, bank_ptr_array, 1);

    #else

	write_array_spm(&spm_matrix->mat_a, DIM, DIM, 
                    factor, 0, bank_ptr_array, 2);		
	
	#endif

	write_array_spm(&spm_matrix->mat_b, DIM, DIM, 
                    factor, factor, bank_ptr_array, 1);	

    stop_transfer = get_cpu_cycles();
    return_transfer = stop_transfer-start_transfer-CYCLE_CALIBRATION;		

    // Start HLS module
	
    start_compute = get_cpu_cycles();               

	*hls_ptr = 1;

	// Poll status of HLS module
    
    while((*hls_ptr) != 1);

    stop_compute = get_cpu_cycles();
    return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;       

    // Read back the data    

    start_transfer = get_cpu_cycles();        

    read_array_spm(&spm_matrix->hw_result, DIM, DIM, 
                   1, NBANKS-1, bank_ptr_array, 1);    

    stop_transfer = get_cpu_cycles();
    return_transfer += stop_transfer-start_transfer-CYCLE_CALIBRATION;    

	// Check results
	err_cnt = compare_arrays_spm(&spm_matrix->hw_result, 
                                 &spm_matrix->sw_result);

    print_benchmark(return_compute, return_transfer);
	
	return err_cnt;
}