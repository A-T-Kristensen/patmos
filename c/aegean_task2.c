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

const int NOC_MASTER = 0;
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <machine/patmos.h>
#include "libcorethread/corethread.h"
#include "libmp/mp.h"
//get_cpucnt(); // returns the number of cores
//get_cpuid(); // returns the core ID

#define LED_RUN_LENGTH 2000
// The hardware address of the LED
#define LED ( *( ( volatile _IODEV unsigned * ) 0xF0090000 ) )
#define UART ( *( ( volatile _IODEV unsigned * ) 0xF0080004 ) )

void blink();
void loop(void* arg);

int main() {

	int num_tokens = 1;
	corethread_t worker_id; // The Core ID

	int* res;

	printf("%d\n", get_cpucnt());
	printf("%d\n", get_cpuid());

	// Start all the cores

	for(int i = 8; i!=0; i--) {
		worker_id = (corethread_t) i;
		corethread_create( &worker_id, &loop, (void*) &num_tokens);
	}

	for(;;);

	return *res;
}

//blink function, period=0 -> ~10Hz, period=255 -> ~1Hz
void blink() {

	unsigned int seed = get_cpu_usecs();
	unsigned int period;

	period = rand_r(&seed) & 0xFFFFFF; // Use the lower 24-bits

	for (;;) {
		for (unsigned int i=period; i!=0; --i) {
			LED = 1;
		}

		for (unsigned int i=period; i!=0; --i) {
			LED = 0;
		}
	}
	return;
}

void loop(void* arg) {
	int num_tokens = *((int*)arg);

	blink();	
}