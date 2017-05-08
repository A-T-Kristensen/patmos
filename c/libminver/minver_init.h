
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

#endif