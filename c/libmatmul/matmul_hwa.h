/*
	This header file contains the functions used in benchmarking
	on hardware and their documentation.

	The initialization functions initializes the matrix values.

	The expected funtions generate the expected result (used for testing).

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License

 */

#ifndef MATMUL_HWA_H_
#define MATMUL_HWA_H_

#include "../libhwa/hwa_lib.h" // Contains the references to _SPM and mat_type etc.

/*
	NAME: matmul_init()

	PARAMETERS:
		* mat_a: Input matrix 1
		* mat_b: Input matrix 2
		* sw_result: Software result, initialised to 0

	RETURNS: None

	DESCRIPTION: Initialises the matrices for computation.

 */

void matmul_init(mat_type mat_a[DIM][DIM],
				 mat_type mat_b[DIM][DIM],
				 mat_type sw_result[DIM][DIM]);

void matmul_init_spm(volatile _SPM mat_type(*mat_a)[DIM][DIM],
					 volatile _SPM mat_type(*mat_b)[DIM][DIM],
					 volatile _SPM mat_type(*sw_result)[DIM][DIM]);

void matmul_init_uncached(volatile _UNCACHED mat_type(*mat_a)[DIM][DIM],
						  volatile _UNCACHED mat_type(*mat_b)[DIM][DIM],
						  volatile _UNCACHED mat_type(*sw_result)[DIM][DIM]);

/*
	NAME: matmul_expected()

	PARAMETERS:
		* mat_a: Input matrix 1
		* mat_b: Input matrix 2
		* sw_result: The expected result from software, multiplication
					 of mat_a and mat_b is stored in sw_result

	RETURNS: None

	DESCRIPTION: Computes the software result for comparison
				 with HwA result (used for testing of correctness)

 */

void matmul_expected(mat_type mat_a[DIM][DIM],
					 mat_type mat_b[DIM][DIM],
					 mat_type sw_result[DIM][DIM]);

/*void matmul_expected_spm(volatile _SPM mat_type (*mat_a)[DIM][DIM],
						 volatile _SPM mat_type (*mat_b)[DIM][DIM],
						 volatile _SPM mat_type (*sw_result)[DIM][DIM]);

void matmul_expected_uncached(volatile _UNCACHED mat_type (*mat_a)[DIM][DIM],
					 		  volatile _UNCACHED mat_type (*mat_b)[DIM][DIM],
				 			  volatile _UNCACHED mat_type (*sw_result)[DIM][DIM]);*/

#endif /* __MATMUL_HWA_H__ */
