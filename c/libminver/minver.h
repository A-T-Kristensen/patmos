

#ifndef MINVER_H_
#define MINVER_H_

#include "../libhwa/hwa_lib.h"

/*
	NAME: read_array()

	PARAMETERS:
		*
		*

	RETURNS:

	DESCRIPTION:
	
 */

int minver_minver(mat_type minver_a[DIM][DIM], int side, mat_type eps);

/*
	NAME: read_array()

	PARAMETERS:
		*
		*

	RETURNS:

	DESCRIPTION:
	
 */

int  minver_mmul(mat_type minver_a[DIM][DIM], mat_type minver_b[DIM][DIM],
        mat_type minver_c[DIM][DIM]);

/*
	NAME: read_array()

	PARAMETERS:
		*
		*

	RETURNS:

	DESCRIPTION:
	
 */

mat_type minver_fabs(mat_type n);

/*
	NAME: read_array()

	PARAMETERS:
		*
		*

	RETURNS:

	DESCRIPTION:
	
 */


/*
	NAME: read_array()

	PARAMETERS:
		*
		*

	RETURNS:

	DESCRIPTION:
	
 */

void set_minver_hwa(mat_type minver_hw[DIM][DIM]);

#endif