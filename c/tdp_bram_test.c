/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded Hello World program: a blinking LED.

    Additional to the blinking LED we write to the UART '0' and '1' (if available).

    Author: Martin Schoeberl
    Copyright: DTU, BSD License
*/

#include <machine/spm.h>
#include <machine/patmos.h>

#include "include/patio.h"
#include "include/bootable.h"

int main() {
	volatile _SPM int *uart_ptr = (volatile _SPM int *) 0xF0080004;
	volatile _SPM int *led_ptr  = (volatile _SPM int *) 0xF0090000;
	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) 0xF00A0000;
	
	int i, j;
	
	for(i = 0; i < 1000; i++){
		*(bram_ptr + i) = i + 1;
	}
	
	if(*bram_ptr) {
		
		for (;;) {
			*uart_ptr = '1';
			for (i=2; i!=0; --i)
				for (j=2; j!=0; --j)
					*led_ptr = 1;


			*uart_ptr = '0';
			for (i=2; i!=0; --i)
				for (j=2; j!=0; --j)
					*led_ptr = 0;

		}		
		
	}


}
