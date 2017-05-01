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
	calibration = 3;

	printf("HWA Running \n");

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

    for(i = 0; i < DIM*DIM; i++)
    {
        *(bank_ptr_array[0] + i) = *((&mat_a[0][0]) + i);
    }

    // Bank 2

    for(i = 0; i < DIM*DIM; i++)
    {
        *(bank_ptr_array[1] + i) = *((&mat_b[0][0]) + i);
    }

    // Start HLS module
	
	*hls_ptr = 1;

	// Poll status of HLS module
    
    while((*hls_ptr) != 1);

    // Read back the data    

    for(i = 0; i < DIM*DIM; i++)
    {
        *((&hw_result[0][0]) + i)= *(bank_ptr_array[2] + i);
    }    
	
	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-calibration;

	printf("%llu \n", return_cycles);

	// Check results

    puts("Checking results");	
	
    for(i = 0; i < DIM*DIM; i++)
    {
		if(  abs(*((&hw_result[0][0])+i) - *((&sw_result[0][0])+i)) > 0.001)
		{
			err_cnt++;	
		}	
    }

	printf("\n");    

    // We now continously loop, showing a pattern on the LEDS
	
	led_blink(err_cnt);

	return 0;
}
