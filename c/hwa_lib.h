#ifndef __HWA_LIB_H__
#define __HWA_LIB_H__

#include <machine/spm.h> // Defines _SPM
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.
#include <machine/rtc.h> // Gives us get_cpu_cycles

#include <stdio.h>
#include <stdlib.h> // For malloc

#include <math.h>

#define BASE_ADDRESS 0xF00B0000
#define ADDR_BITS 16

#define DIM 32
#define NBANKS 3

typedef float mat_type;

#define LED_RUN_LENGTH 2000


// bank_ptrs generates an array of pointers to the bram blocks

volatile _IODEV unsigned long** bank_ptrs(unsigned long nbanks) {

	int i;
	unsigned long bank_bits = (unsigned long) ceil(log2(nbanks));

	volatile _IODEV unsigned long** bank_ptr_array = (volatile _IODEV unsigned long**) malloc(bank_bits*sizeof(unsigned long*));

	for(i = 0; i < nbanks; i++) {
		bank_ptr_array[i] = (volatile _IODEV unsigned long *) ((i << (ADDR_BITS - bank_bits)) + BASE_ADDRESS);
	}

	return bank_ptr_array;
}

#endif /* __HWA_LIB_H__ */
