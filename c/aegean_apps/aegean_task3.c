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
#include <machine/spm.h> // Defines _SPM
#include "libcorethread/corethread.h"
#include "libmp/mp.h"
//get_cpucnt(); // returns the number of cores
//get_cpuid(); // returns the core ID

#define MP_CHAN_NUM_BUF 2
#define MP_CHAN_BUF_SIZE 40

// The hardware address of the LED
#define LED ( *( ( volatile _IODEV unsigned * ) 0xF0090000 ) )
#define UART ( *( ( volatile _IODEV unsigned * ) 0xF0080004 ) )

void blink();
void loop(void* arg);

void slave1(void* param);
void slave2(void* param);
void slave3(void* param);

int main() {

	int num_tokens = 1;
	corethread_t worker_id = 1; // The Core ID

	int* res;

	printf("%d\n", get_cpucnt());
	printf("%d\n", get_cpuid());

	// Start all the cores
	corethread_create( &worker_id, &slave1, (void*) &num_tokens);
	worker_id++;
	corethread_create( &worker_id, &slave2, (void*) &num_tokens);
	worker_id++;
	corethread_create( &worker_id, &slave3, (void*) &num_tokens);

	return *res;
}

//blink function, period=0 -> ~10Hz, period=255 -> ~1Hz
void blink() {
	unsigned int period = 255;

	//for (;;) {
		for (int i=400000+14117*period; i!=0; --i) {
			LED = 1;
		}

		for (int i=400000+14117*period; i!=0; --i) {
			LED = 0;
		}
	//}
	return;
}

void loop(void* arg) {
	int num_tokens = *((int*)arg);

	blink();	
}

// Slave function running on core 1
void slave1(void* param) {

	unsigned int token = 1;

	// Create the sink port for channel 3
	qpd_t * chan3 = mp_create_qport(3, SINK,
	MP_CHAN_BUF_SIZE, MP_CHAN_NUM_BUF);

	// Create the source port for channel 1
	qpd_t * chan1 = mp_create_qport(1, SOURCE,
	MP_CHAN_BUF_SIZE, MP_CHAN_NUM_BUF);
	mp_init_ports();

	for(;;) {

		blink();

		// Writing an unsigned integer value to the channel
		// write buffer and sending it.
		*( volatile int _SPM * ) ( chan1->write_buf ) = token;
		mp_send(chan1,0); // Calls mp_nbsend until returning success

		// Receiving, reading and acknowledge reception of
		// an unsigned integer value from the channel read buffer
		mp_recv(chan3,0);
		token = *(( volatile int _SPM * ) ( chan3->read_buf ));
		mp_ack(chan3,0);
	}
	

	return;
}

// Slave function running on core 2
void slave2(void* param) {

	unsigned int token = 0;

	// Create the sink port for channel 1
	qpd_t * chan1 = mp_create_qport(1, SINK,
	MP_CHAN_BUF_SIZE, MP_CHAN_NUM_BUF);

	// Create the source port for channel 2
	qpd_t * chan2 = mp_create_qport(2, SOURCE,
	MP_CHAN_BUF_SIZE, MP_CHAN_NUM_BUF);
	mp_init_ports();

	// Do something

	for(;;) {
		mp_recv(chan1,0);
		token = *(( volatile int _SPM * ) ( chan1->read_buf ));
		mp_ack(chan1,0);

		blink(); // This only runs when core 1 writes, so it automatically stalls
				 // this is due to us using mp_recv, since it reads in a loop.

		*( volatile int _SPM * ) ( chan2->write_buf ) = token;
		mp_send(chan2,0); // Calls mp_nbsend until returning success		
	}
	
	return;
}

// Slave function running on core 2
void slave3(void* param) {

	int token = 0;

	// Create the sink port for channel 2
	qpd_t * chan2 = mp_create_qport(2, SINK,
	MP_CHAN_BUF_SIZE, MP_CHAN_NUM_BUF);

	// Create the source port for channel 3
	qpd_t * chan3 = mp_create_qport(3, SOURCE,
	MP_CHAN_BUF_SIZE, MP_CHAN_NUM_BUF);
	mp_init_ports();

	// Do something

	for(;;) {
		mp_recv(chan2,0);
		token = *(( volatile int _SPM * ) ( chan2->read_buf ));
		mp_ack(chan2,0);	

		blink();

		*( volatile int _SPM * ) ( chan3->write_buf ) = token;
		mp_send(chan3,0); 		
	}	

	return;
}