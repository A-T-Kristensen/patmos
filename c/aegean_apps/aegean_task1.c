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

// The hardware address of the LED
#define LED ( *( ( volatile _IODEV unsigned * ) 0xF0090000 ) )
#define UART ( *( ( volatile _IODEV unsigned * ) 0xF0080004 ) )

void blink(int period);
void loop(void* arg);

int main() {

	/*
		TODO, have all worker_ids in an array.
		and then just use this for everything.
	*/

	int blink_period = 255;
	corethread_t worker_id = 1; // The Core ID

	int* res;

	int num_cores = get_cpucnt();

	printf("%d\n", num_cores);
	printf("%d\n", get_cpuid());

	// Start all the cores

	for(int i = 1; i < num_cores; i++) {
		worker_id = (corethread_t) i;
		corethread_create( &worker_id, &loop, (void*) &blink_period);
	}

	for(int i = 1; i < num_cores; i++) {
		worker_id = (corethread_t) i;
		corethread_join(worker_id, (void **)& res);
		printf("Corenum = %d\n", *res);
	}	

	return 0;
}

//blink function, period=0 -> ~10Hz, period=255 -> ~1Hz
void blink(int period) {
	int count;

	for (count = 10; count!=0; count--) {
		for (int i=400000+14117*period; i!=0; --i) {
			LED = 1;
		}

		for (int i=400000+14117*period; i!=0; --i) {
			LED = 0;
		}
	}
	return;
}

void loop(void* arg) {

	int retval = get_cpuid();

	int period = *((int*)arg);
	blink(period);	

	corethread_exit(&retval);

	return;
}