/*
 *	This is a minimal C program executed on the FPGA version of Patmos.
 *	An embedded test of a vivado hls module: writing 1, 2, 3 to BRAM, and expecting 2, 4, 6 out.
 *
 *	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
 *	Copyright: DTU, BSD License
 */


// Files required for memory mapped IO devices
// patmos.h defines _IODEV, used to access memory mapped IO devices.

#include "hwa_lib.h"

int main() 
{

	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) BRAM_BASE;
	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;    
	
	int i, j, err_cnt = 0;
	
	int bram_in[3] = {1, 2, 3};
	int bram_out[3];
	int gold[3] = {2, 4, 6};

    for(i = 0; i < 3; i++)
    {
        *(bram_ptr + i) = bram_in[i];
    }

    // Start HwA

	*hls_ptr = 1;

	// Poll status of HwA
    
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
	
	led_blink(err_cnt);

	return 0;
} 