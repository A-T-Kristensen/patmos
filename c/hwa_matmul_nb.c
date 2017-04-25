/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded test of a vivado hls module: Matrix multiplication on an array of dimension DIM partitioned
    into NBANKS memory banks

    Author: Andreas T. Kristensen 
    Copyright: DTU, BSD License
*/

// These are used to write to SPM and IO devices

#include "hwa_lib.h"

#define DIM 4
#define NBANKS 3

#define LED_RUN_LENGTH 2000

typedef float mat_type;

int main() 
{

	int i, j, k;
	int err_cnt = 0;
	//unsigned long long start_cycle, stop_cycle, calibration;	

	volatile _IODEV mat_type** bank_ptr_array = (volatile _IODEV mat_type**) bank_ptrs(NBANKS);

	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;
	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) 0xF00C0000;    

	mat_type mat_a[DIM][DIM];
	mat_type mat_b[DIM][DIM];
	mat_type sw_result[DIM][DIM], hw_result[DIM][DIM];

	static unsigned long long start_cycle, stop_cycle, calibration;	
	static unsigned long long return_cycles = 0;		

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
        printf("%f ", *((&hw_result[0][0]) + i) );        

        if((i+1) % DIM == 0) {
        	printf("\n");
        }            

		if(*((&hw_result[0][0])+i) != *((&sw_result[0][0])+i))
		{
			err_cnt++;	
		}	
    }

	printf("\n");    

    // We now continously loop, showing a pattern on the LEDS
	
	if(!err_cnt) 
	{
		puts("Results correct");				
		for (;;) 
		{
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 3;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
			
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 15;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
			
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 63;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;			
		}		
	} 

	else 
	{
		puts("Results incorrect");			
		for (;;) 
		{
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
			
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 7; 	
	  	}
	}
}
