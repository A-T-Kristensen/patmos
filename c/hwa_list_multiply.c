/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded test of a vivado hls module: writing 1, 2, 3 to BRAM, and expecting 2, 4, 6 out.

    Author: Andreas T. Kristensen 
    Copyright: DTU, BSD License
*/

// Files required for memory mapped IO devices
// patmos.h defines _IODEV, used to access memory mapped IO devices.

#include <machine/patmos.h>

#include <stdio.h>

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

    // Start HLS module

	*hls_ptr = 1;

	// Poll status of HLS module
    
    while((*hls_ptr) != 1);
	
	// Read back data from BRAM

    for(i = 0; i < 3; i++)
    {
        bram_out[i] = *(bram_ptr + i);
    }

    // Check results

    for(i = 0; i < 3; i++)
    {
        printf("%d \n", bram_out[i]);
		
		if(bram_out[i] != gold[i])
		{
			err_cnt++;	
		}
    }    

    // We now continously loop, showing a pattern on the LEDS
	
	if(!err_cnt) 
	{
		puts("Results correct"); 	

		for (;;) 
		{
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
