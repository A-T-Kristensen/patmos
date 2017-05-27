/*
	This header file contains the functions used in benchmarking
	on hardware and their documentation.

	The set_minver() functions are used to set the matrices
	with the values of an invertible matrix.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License

 */


#ifndef MINVER_INIT_H_
#define MINVER_INIT_H_

#include "../libhwa/hwa_lib.h"

/*
	NAME: set_minver()

	PARAMETERS:
		* minver_a: Input matrix.

	RETURNS: None

	DESCRIPTION: set_minver() sets the value of minver_a
				 to that of an invertible matrix.

 */

void set_minver(mat_type minver_a[DIM][DIM]);

void set_minver_spm(volatile _SPM mat_type(*minver_a)[DIM][DIM]);

void set_minver_uncached(volatile _UNCACHED mat_type(*minver_a)[DIM][DIM]);


#endif