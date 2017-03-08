/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded test of a vivado hls module: writing 1, 2, 3 to bram, and expecting 2, 4, 6 out.

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
	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) 0xF00C0000;    
	
	int i, j, err_cnt = 0;
	
	int bram_in[3] = {1, 2, 3};
	int bram_out[3];
	int gold[3] = {2, 4, 6};

    for(i = 0; i < 3; i++)
    {
        *(bram_ptr + i) = bram_in[i];
    }

    // Start the hardware accelerator
	
	*hls_ptr = 1;

	// Poll status
    
    while((*hls_ptr) != 1);
	
	// Check the result once finished
	
    for(i = 0; i < 3; i++)
    {
        bram_out[i] = *(bram_ptr + i);
		
		if(bram_out[i] != gold[i])
		{
			err_cnt++;	
		}
    }

    // We now continously loop, showing the results on the LEDs in binary
	
	if(!err_cnt) 
	{
		//Print the output values using LEDS
		for (;;) 
		{
			// Result in out[
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = bram_out[0] ==  gold[0] ? 3 : 1;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
			
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = bram_out[1] ==  gold[1] ? 15 : 1;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
			
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = bram_out[2] ==  gold[2] ? 63 : 1;

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
