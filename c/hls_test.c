/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded Hello World program: a blinking LED.

    Additional to the blinking LED we write to the UART '0' and '1' (if available).

    Author: Martin Schoeberl
    Copyright: DTU, BSD License
*/

#include <machine/spm.h>

int main() {
	volatile _SPM int *uart_ptr = (volatile _SPM int *) 0xF0080004;
	volatile _SPM int *led_ptr  = (volatile _SPM int *) 0xF0090000;
	volatile int *bram_ptr = (volatile int *) 0xF00A0000;
	volatile int *hls_ptr = (volatile int *) 0xF00B0000;    
	
	int i, j, cnt = 0;
    char char_out = 0;
    
    for(i = 3; i!=0; --i){
        *(bram_ptr + i) = i;
    }
	
	*hls_ptr = 1;
    
    while( (*hls_ptr) != 1) {
        cnt++;
    };
    
    char_out = (char) cnt + '0';
	
	if( (*hls_ptr) == 1 ) {
		
		for (;;) {
			*uart_ptr = char_out;
			for (i=2000; i!=0; --i)
				for (j=2000; j!=0; --j)
					*led_ptr = 1;


			*uart_ptr = char_out;
			for (i=2000; i!=0; --i)
				for (j=2000; j!=0; --j)
					*led_ptr = 0;

		}		
		
	}


}
