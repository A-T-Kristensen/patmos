/*
	This header file contains the functions used to generate
	the correct results to check with that produced by the
	HwA.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License

 */

#ifndef MINVER_H_
#define MINVER_H_

#include "../libhwa/hwa_lib.h"

/*
	NAME: minver_fabs()

	PARAMETERS:
		* n: The input value.

	RETURNS:  The absolute value of n.

	DESCRIPTION: minver_fabs() computes the absolute value of the input n.

 */

float minver_fabs(float n);

/*
	NAME: minver_minver()

	PARAMETERS:
		* minver_a: The input matrix to compute the inverted matrix.
		* side: The size of the matrix (side X side)
		* eps: Floating-point relative accuracy

	RETURNS:

	DESCRIPTION: Returns the inverted matrix of minver_a.

 */

int minver_minver(float minver_a[DIM][DIM], int side, float eps);

#endif