/*
	This header file contains the forward declarations
	for a number of functions used in testing the 
	HwAs.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License
	
 */

#ifndef HWA_TEST_H_
#define HWA_TEST_H_

#include "hwa_lib.h"

/*
	NAME: compare_arrays()

	PARAMETERS:
		* hw_result: The hardware result.
		* sw_result: The software result

	RETURNS: The error count.

	DESCRIPTION: Determines if the result from the 
				 HwA differs from that of the software.

 */

int compare_arrays(mat_type hw_result[ROWS][COLS], 
				   mat_type sw_result[ROWS][COLS]);

int compare_arrays_spm(volatile _SPM mat_type (*hw_result)[ROWS][COLS], 
					 volatile _SPM mat_type (*sw_result)[ROWS][COLS]); 

int compare_arrays_uncached(volatile _UNCACHED mat_type (*hw_result)[ROWS][COLS], 
						    volatile _UNCACHED mat_type (*sw_result)[ROWS][COLS]);

/*
	NAME: compare_vectors()

	PARAMETERS:
		* hw_result: The hardware result.
		* sw_result: The software result
		* length: The length of the vector

	RETURNS: The error count.

	DESCRIPTION: Determines if the result from the 
				 HwA differs from that of the software.
	
 */

int compare_vectors(mat_type hw_result[], 
					mat_type sw_result[],
					int length);

int compare_vectors_spm(volatile _SPM mat_type (*hw_result)[], 
						volatile _SPM mat_type (*sw_result)[],
						int length);

int compare_vectors_uncached(volatile _UNCACHED mat_type (*hw_result)[], 
							 volatile _UNCACHED mat_type (*sw_result)[],
							 int length);

/*
	NAME: led_blink()

	PARAMETERS:
 		* err_cnt: The number of errors in the calculations between
 				   the HwA and the software.

	RETURNS: None

	DESCRIPTION: led_blink() blinks the LEDs on the FPGA in
 				 different patterns depending on whether the result is correct
	
 */

void led_blink(int err_cnt);

  /*
	NAME: print_benchmark()

	PARAMETERS:
		*return_compute: The clock cycles for computation.
		*return_transfer: The clock cycles for data transfer

	RETURNS: None

	DESCRIPTION: Prints the benchmark results properly
	
 */

void print_benchmark(long long unsigned return_compute, 
					 long long unsigned return_transfer);

#endif /* __HWA_TEST_H__ */