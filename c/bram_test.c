/*
    This is a minimal C program used for WCET test for writing to
    the bram.

    Author: Andreas T. Kristensen
    Copyright: BSD License
*/

#include <machine/spm.h> 	// Defines _SPM
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.
#include <machine/rtc.h> 	// Gives us get_cpu_cycles

#include <stdio.h>
#include <stdlib.h>

#define DIM 2

void bram_main(void) __attribute__((noinline));

void _Pragma("entrypoint") bram_main(void)
{

	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) 0xF00B0000;

	unsigned long long calib_start, calib_end;	
	calib_start = get_cpu_cycles();	
	calib_end = get_cpu_cycles();		

	unsigned long long start_write, stop_write, return_write = 0;	
	unsigned long long start_read, stop_read, return_read = 0;		

	volatile int i;
	int temp[DIM];
	volatile _SPM int* test_spm = (volatile _SPM int *) SPM_BASE;

	//printf("Test writing to my bram\n");

	start_write = get_cpu_cycles();	

	// Write data to my BRAM

	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < DIM; i++) {
		*(bram_ptr + i) = i + 1;
	}

	stop_write = get_cpu_cycles();
	return_write = stop_write-start_write-6;		

	start_read = get_cpu_cycles();		

	// Read back data from BRAM

	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < DIM; i++) {
		temp[i] = *(bram_ptr + i);
	}

	stop_read = get_cpu_cycles();
	return_read = stop_read-start_read-6;	

	printf("Read: %llu\n", return_read);
	printf("Write: %llu\n", return_write);

	for(i = 0; i < DIM; i++) {
		*(test_spm + i) = i + 1;
	}


	start_write = get_cpu_cycles();	

	// Write data to BRAM from SPM

	printf("Test writing to my bram from SPM\n");	

	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < DIM; i++) {
		*(bram_ptr + i) = *(test_spm + i);
	}

	stop_write = get_cpu_cycles();
	return_write = stop_write-start_write-6;		

	start_read = get_cpu_cycles();		

	// Read back data from BRAM

	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < DIM; i++) {
		*(test_spm + i) = *(bram_ptr + i);
	}

	stop_read = get_cpu_cycles();
	return_read = stop_read-start_read-6;	

	printf("Read: %llu\n", return_read);
	printf("Write: %llu\n", return_write);

	// Write data to SPM

	printf("Test writing to SPM\n");	

	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < DIM; i++) {
		*(test_spm + i) = 1 + i;
	}

	stop_write = get_cpu_cycles();
	return_write = stop_write-start_write-6;		

	start_read = get_cpu_cycles();		

	// Read back data from SPM

	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < DIM; i++) {
		temp[i]  = *(test_spm + i);
	}

	stop_read = get_cpu_cycles();
	return_read = stop_read-start_read-6;	

	printf("Read: %llu\n", return_read);
	printf("Write: %llu\n", return_write);	

}

int main()
{

	bram_main();

	return 0;
}

