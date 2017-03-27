/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded test of a bram module: writing to the bram and if the values read back are correct, blink LED

    Author: Andreas T. Kristensen 
    Copyright: DTU, BSD License
*/

//We need this if we want to make it a bootapp

#include "include/patio.h"
#include "include/bootable.h"

// These are used to write to SPM and IO devices

#include <machine/spm.h> // Defines _SPM
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.

#define LED_RUN_LENGTH 2

int main() 
{
	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;
	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) 0xF00B0000;
	
	int i, j;
	int temp;
	int err_cnt = 0;

	// WRITE DATA TO BRAM
	
	for(i = 0; i < 10; i++)
	{
		*(bram_ptr + i) = i + 1;
	}
	
	// READ BACK DATA AND CHECK IF CORRECT
	
	for(i = 0; i < 10; i++)
	{
		temp = *(bram_ptr + i);

		if(temp != (i+1))
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
					*led_ptr = 7; 	// Blinks 111
	  	}
	}
}
