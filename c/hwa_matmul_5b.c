/*
 *	This is a minimal C program executed on the FPGA version of Patmos.
 *	An embedded test of a vivado HLS HwA module: Matrix multiplication on 
 *	an array of dimension DIM partitionen into NBANKS memory banks.
 *
 *	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
 *	Copyright: DTU, BSD License
 */

#include "hwa_lib.h"

int main() 
{

	int i, j, k;
	int err_cnt = 0;
	//unsigned long long start_cycle, stop_cycle, calibration;	

	volatile _IODEV mat_type** bank_ptr_array = (volatile _IODEV mat_type**) bank_ptrs(NBANKS);
	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;    

	mat_type mat_a[DIM][DIM];
	mat_type mat_b[DIM][DIM];
	mat_type sw_result[DIM][DIM], hw_result[DIM][DIM];

	unsigned long long start_cycle, stop_cycle, calibration;	
	unsigned long long return_cycles = 0;		

	start_cycle = get_cpu_cycles();
	stop_cycle = get_cpu_cycles();
	calibration = stop_cycle-start_cycle;

	printf("%llu \n", calibration);

	//printf("%d \n", get_cpu_freq()); // is this accurate?

	// Initialize matrices

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			mat_a[i][j] = i+j+1;
			mat_b[i][j] = i+j+1+DIM;
	      	sw_result[i][j] = 0;      				
		}
	}

	start_cycle = get_cpu_cycles();

   // Generate the expected result

   for(i = 0; i < DIM; i++) {
      for(j = 0; j < DIM; j++) {
         for(k = 0; k < DIM; k++) {
            sw_result[i][j] += mat_a[i][k] * mat_b[k][j];
         }
      }
   }	

	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-calibration;
	printf("%llu \n", return_cycles);

   // Write to BRAM

	start_cycle = get_cpu_cycles();

   // Bank 1
	// divide factor
	int factor = 2;
	int n = DIM; // the # columns
	int m = DIM; // the # rows
	int a_bank0 = 0;
	int b_bank0 = 2;	
	int a_banks = 2;
	int b_banks = 2;

	// Write A, dim = 2

	for(i = 0; i < a_banks; i++ ) {
		for(j = 0; j < m; j++){
			for(k = 0; k < n/factor; k++){
				*(bank_ptr_array[i+a_bank0] + k + m*j/factor) = mat_a[j][k+i*n/factor];
			}
		}
	}

    // Bank 2
    
  	// Write B, dim = 1

	for(i = 0; i < b_banks; i++ ) {
		for(j = 0; j < m/factor; j++){
			for(k = 0; k < n; k++){
				*(bank_ptr_array[i+b_bank0] + k + n*j) = mat_b[j+i*m/factor][k];
			}
		}
	}    

    // Start HLS module
	
	*hls_ptr = 1;

	// Poll status of HLS module
    
    while((*hls_ptr) != 1);

    // Read back the data    

    for(i = 0; i < DIM*DIM; i++)
    {
        *((&hw_result[0][0]) + i)= *(bank_ptr_array[NBANKS-1] + i);
    }    
	
	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-calibration;

	printf("%llu \n", return_cycles);

	// Check results

    puts("Checking results");	
	
    for(i = 0; i < DIM*DIM; i++)
    {
		if(*((&hw_result[0][0])+i) != *((&sw_result[0][0])+i))
		{
			err_cnt++;	
		}	
    }

	printf("\n");    

    // We now continously loop, showing a pattern on the LEDS
	
	led_blink(err_cnt);

	return 0;
}
