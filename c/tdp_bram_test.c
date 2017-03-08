/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded test of a bram module: writing to the bram and if the values read back are correct, blink LED

    Additional to the blinking LED we write to the UART '0' and '1' (if available).

    Author: Andreas T. Kristensen 
    Copyright: DTU, BSD License
*/

//We need this if we want to make it a bootapp

//#include "include/patio.h"
//#include "include/bootable.h"

// These are used to write to SPM and IO devices

#include <machine/spm.h> // Defines _SPM
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.

#define LED_RUN_LENGTH 2000

int main() 
{
	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;
	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) 0xF00B0000;
	
	int i, j;
	int temp = 0;
	int cnt = 0;

	// Now write to bram
	
	for(i = 0; i < 10; i++)
	{
		*(bram_ptr + i) = i + 1;
	}
	
	//Now get data from bram and show this by flashing led
	
	for(i = 0; i < 10; i++){
		
		if(*(bram_ptr + i) == (i+1))
		{ 			
			cnt++;
		}
	}
	
	if(cnt == 10)
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
		return 0;
	}
}
