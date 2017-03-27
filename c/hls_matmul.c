/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded test of a vivado hls module: Matrix multiplication on an array of dimension DIM

    Author: Andreas T. Kristensen 
    Copyright: DTU, BSD License
*/

// These are used to write to SPM and IO devices

#include <machine/spm.h> // Defines _SPM
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.

#include <stdio.h>

#define DIM 4

#define LED_RUN_LENGTH 2000

int main() 
{

	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;
	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) 0xF00B0000;
	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) 0xF00C0000;    
	
	int mat_a[DIM][DIM];
	int mat_b[DIM][DIM];
	int sw_result[DIM][DIM], hw_result[DIM][DIM];
	int in_bram[3*DIM][DIM]; // Data to be written to the bram.

	int err_cnt = 0;
	int i, j;

	// Initialize matrices

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			mat_a[i][j] = i+j+1;
			in_bram[i][j]  = mat_a[i][j];

			mat_b[i][j] = i+j+1+DIM;
			in_bram[i+DIM][j]  = mat_b[i][j];			
		}
	}

   // Generate the expected result
   for(i = 0; i < DIM; i++) {
      for(j = 0; j < DIM; j++) {
         for(int k = 0; k < DIM; k++) {
            sw_result[i][j] += mat_a[i][k] * mat_b[k][j];
         }
      }
   }	

   // Write to bram

   //We write linearly
    for(i = 0; i < 3*DIM*DIM; i++)
    {
        *(bram_ptr + i) = *((&in_bram[0][0]) + i);
        printf("%d ", *(bram_ptr + i)); // Check written value

        if((i+1) % DIM == 0) {
        	printf("\n");
        }
    }

    printf("\n");

    // START HLS MODULE
	
	*hls_ptr = 1;

	// POLL STATUS OF HLS MODULE
    
    while((*hls_ptr) != 1);

    puts("Checking results");
	
	// CHECK RESULTS
	
    for(i = 0; i < DIM*DIM; i++)
    {
        *((&hw_result[0][0]) + i) = *(bram_ptr + i + 2*DIM*DIM); // Increment by 2*DIM*DIM for result
        printf("%d ", *((&hw_result[0][0]) +i) );

        if((i+1) % DIM == 0) {
        	printf("\n");
        }        
		
		if(*((&hw_result[0][0])+i) != *((&sw_result[0][0])+i))
		{
			err_cnt++;	
		}
    }

    // We now continously loop, showing a pattern on the LEDS
	
	if(!err_cnt) 
	{
		puts("Results correct"); // puts for strings!		
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
		puts("Results incorrect"); // puts for strings!		
		// Flash 111 LEDS		
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
