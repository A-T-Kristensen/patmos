/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded Hello World program: a blinking LED.

    Additional to the blinking LED we write to the UART '0' and '1' (if available).

    Author: Martin Schoeberl
    Copyright: DTU, BSD License
*/

//We need this if we want to make it a bootapp
#include <machine/patmos.h>
#include "include/patio.h"
#include "include/bootable.h"

#include <machine/spm.h>

int main() {
	volatile _SPM int *led_ptr  = (volatile _SPM int *) 0xF0090000;
	volatile int *bram_ptr = (volatile int *) 0xF00B0000;
	volatile int *hls_ptr = (volatile int *) 0xF00C0000;    
	
	int i, j, cnt = 0;
	
	int in[3] = {1, 2, 3};
	int out[3];
	int res[3] = {2, 4, 6};

    for(i = 0; i < 3; i++){
        *(bram_ptr + i) = in[i];
    }
	
	*hls_ptr = 1;
    
    while( (*hls_ptr) != 1);
	
	// Check the result
	
    for(i = 0; i < 3; i++){
        out[i] = *(bram_ptr + i);
		
		if(out[i] != res[i]){
			cnt++;	
		}
			
    }	
	
	if(!cnt) {
		
		//Print the output values using LEDS
		
		for (;;) {

			// Result in out[
			for (i=2000; i!=0; --i)
				for (j=2000; j!=0; --j)
					*led_ptr = out[0];

			for (i=2000; i!=0; --i)
				for (j=2000; j!=0; --j)
					*led_ptr = 0;
			
			for (i=2000; i!=0; --i)
				for (j=2000; j!=0; --j)
					*led_ptr = out[1];

			for (i=2000; i!=0; --i)
				for (j=2000; j!=0; --j)
					*led_ptr = 0;
			
			for (i=2000; i!=0; --i)
				for (j=2000; j!=0; --j)
					*led_ptr = out[2];

			for (i=2000; i!=0; --i)
				for (j=2000; j!=0; --j)
					*led_ptr = 0;			

		}		
		
	} else {
		return 0;	
	}


}
