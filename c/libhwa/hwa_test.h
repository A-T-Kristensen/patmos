/*
	This header file contains the forward declarations
	for a number of functions used in testing the 
	HwAs.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: DTU, BSD License
	
 */

#ifndef HWA_TEST_H_
#define HWA_TEST_H_

#include "hwa_lib.h"

/*
	NAME: led_blink()

	PARAMETERS:
 		* err_cnt: The number of errors in the calculations between
 				   the HwA and the software.

	RETURNS: void

	DESCRIPTION: led_blink() blinks the LEDs on the FPGA in
 				 different patterns depending on whether the result is correct
	
 */

void led_blink(int err_cnt);

/*
	NAME: compare_arrays()

	PARAMETERS:
		* hw_result
		* sw_result

	RETURNS: The error count.

	DESCRIPTION: Determines if the result from the HwA differs from that of the software.

 */

int compare_arrays(mat_type hw_result[DIM][DIM], 
				 mat_type sw_result[DIM][DIM]);

int compare_arrays_spm(volatile _SPM mat_type (*hw_result)[DIM][DIM], 
					 volatile _SPM mat_type (*sw_result)[DIM][DIM]); 

int compare_arrays_uncached(volatile _UNCACHED mat_type (*hw_result)[DIM][DIM], 
						  volatile _UNCACHED mat_type (*sw_result)[DIM][DIM]);

/*
	NAME: 

	PARAMETERS:
		*
		*

	RETURNS:

	DESCRIPTION:
	
 */

  /*
	NAME: 

	PARAMETERS:
		*
		*

	RETURNS:

	DESCRIPTION:
	
 */

void print_benchmark(long long unsigned return_compute, long long unsigned return_transfer);


#endif /* __HWA_TEST_H__ */
