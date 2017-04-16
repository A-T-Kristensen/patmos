/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded test of a vivado hls module: Matrix multiplication on an array of dimension DIM

    Author: Andreas T. Kristensen 
    Copyright: DTU, BSD License
*/

//We need this if we want to make it a bootapp

#include "include/patio.h"
#include "include/bootable.h"

// These are used to write to SPM and IO devices

#include <machine/spm.h> // Defines _SPM
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.

#define DIM 4

#define LED_RUN_LENGTH 2

int main() 
{

	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;
	volatile _SPM int *spm_ptr  = (volatile _SPM int *) 0x00010000;
	
	int hw_result[DIM][DIM];
	int in_spm[DIM][DIM]; // Data to be written to the bram.

	int err_cnt = 0;
	int i, j;

	// Initialize matrices

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			in_spm[i][j]  = i+j+1;
		}
	}

   // Write to bram

   //We write linearly
    for(i = 0; i < DIM*DIM; i++)
    {
        *(spm_ptr + i) = *((&in_spm[0][0]) + i);
    }
	
    for(i = 0; i < DIM*DIM; i++)
    {
        *((&hw_result[0][0]) + i) = *(spm_ptr + i); // Increment by 2*DIM*DIM for result
    }

    // We now continously loop, showing a pattern on the LEDS
	
	if(!err_cnt) 
	{
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
