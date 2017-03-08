/*
    This is a minimal C program executed on the FPGA version of Patmos.
    An embedded Hello World program: a blinking LED.

    Additional to the blinking LED we write to the UART '0' and '1' (if available).

    Author: Martin Schoeberl
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
	volatile _IODEV int *uart_ptr = (volatile _IODEV int *) 0xF0080004;
	
	int i, j;

	for (;;) 
	{
		*uart_ptr = '1';

		for (i=LED_RUN_LENGTH; i!=0; --i)
			for (j=LED_RUN_LENGTH; j!=0; --j)
				*led_ptr = 1;

		*uart_ptr = '0';

		for (i=LED_RUN_LENGTH; i!=0; --i)
			for (j=LED_RUN_LENGTH; j!=0; --j)
				*led_ptr = 0;
	}
}
