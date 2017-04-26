/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded test of a BRAM module: writing to the BRAM and if the values read back are correct.
    The LEDs will blink in specific patterns for success or failure.

    Author: Andreas T. Kristensen 
    Copyright: DTU, BSD License
*/

// Required to make bootapp

#include "include/patio.h"
#include "include/bootable.h"

// Files required for memory mapped IO devices
// patmos.h defines _IODEV, used to access memory mapped IO devices.

#include <machine/patmos.h> 

#define LED_RUN_LENGTH 2

int main() 
{
	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;
	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) 0xF00B0000;
	
	int i, j;
	int n = 10;
	int temp[n];
	int err_cnt = 0;

	// Write data to BRAM
	
	for(i = 0; i < n; i++)
	{
		*(bram_ptr + i) = i + 1;
	}
	
	// Read back data from BRAM
	
	for(i = 0; i < n; i++)
	{
		temp[i] = *(bram_ptr + i);
	}

	// Check data

	for(i = 0; i < n; i++)
	{
		if(temp[i] != (i+1))
		{ 			
			err_cnt++;
		}		
	}	
	
	if(!err_cnt)
	{
		for(;;)
		{
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 1;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
		}		
	} 

	else 
	{	
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
