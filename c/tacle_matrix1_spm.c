/*

  This program is part of the TACLeBench benchmark suite.
  Version V 1.x

  Name: matrix1

  Author: Juan Martinez Velarde

  Function: Generic matrix - multiply benchmarking

    This program performs a matrix multiplication of the form C=AB,
    where A and B are two dimensional matrices of arbitrary dimension.
    The only restriction os that the inner dimension of the arrays must
    be greater than 1.

      A[X x Y] * B[Y x Z] = C[X x Z]

                       |a11     a12     ..      a1y|
                       |a21     a22     ..      a2y|
      matrix A[X x Y]= |..      ..      ..     ..  |
                       |a(x-1)1 a(x-1)2 ..  a(x-1)y|
                       |ax1     ax2     ..      axy|


                       |b11     b12     ..     b1z|
                       |b21     b22     ..     b2z|
      matrix B[Y x Z]= |..      ..      ..     .. |
                       |b(y-1)1 b(y-1)2 .. b(y-1)z|
                       |by1     by2     ..     byz|

                       |c11     c12     ..     c1z|
                       |c21     c22     ..     c2z|
      matrix C[X x Z]= |..      ..      ..     .. |
                       |c(x-1)1 c(x-1)2 .. c(x-1)z|
                       |cx1     cx2     ..     cxz|

      matrix elements are stored as

      A[X x Y] = { a11, a12, .. , a1y,
                   a21, a22, .. , a2y,
                   ...,
                   ax1, ax2, .. , axy}

      B[Y x Z] = { b11, b21, .., b(y-1)1, by1, b12, b22, .. , b(y-1)z, byz }

      C[X x Z] = { c11, c21, .. , c(x-1)1, cx1, c12, c22, .. ,c(x-1)z, cxz }

  Source: DSP-Stone
          http://www.ice.rwth-aachen.de/research/tools-projects/entry/detail/dspstone

  Changes: no major functional changes

  License: may be used, modified, and re-distributed freely

*/


/*
  Macro definitions
*/

#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_test.h"

#define X DIM /* first dimension of array A */
#define Y DIM /* second dimension of array A, first dimension of array B */
#define Z DIM /* second dimension of array B */

/*
  Declaration of global variables
*/

struct matrix {
	mat_type matrix1_A[X * Y];
	mat_type matrix1_B[Y * Z];
	mat_type matrix1_C[X * Z];
};

volatile _SPM struct matrix *spm_matrix = (volatile _SPM struct matrix *) SPM_BASE;

/*
  Forward declaration of functions
*/

void matrix1_pin_down(void);
void matrix1_main(void) __attribute__((noinline));;
int main(void);


/*
  Initialization functions
*/

void matrix1_pin_down(void)
{

	int i;
	volatile mat_type x = 1;

	_Pragma("loopbound min SIZE max SIZE")
	for(i = 0 ; i < X * Y; i++)
		spm_matrix->matrix1_A[i] = x ;

	_Pragma("loopbound min SIZE max SIZE")
	for(i = 0 ; i < Y * Z ; i++)
		spm_matrix->matrix1_B[i] = x ;

	_Pragma("loopbound min SIZE max SIZE")
	for(i = 0 ; i < X * Z ; i++)
		spm_matrix->matrix1_C[i] = 0 ;
}

/*
  Main functions
*/

void _Pragma("entrypoint") matrix1_main(void)
{

	volatile _SPM mat_type *p_a = &(spm_matrix->matrix1_A[0]);
	volatile _SPM mat_type *p_b = &(spm_matrix->matrix1_B[0]);
	volatile _SPM mat_type *p_c = &(spm_matrix->matrix1_C[0]);

	int f, i, k;

	_Pragma("loopbound min DIM max DIM")
	for(k = 0; k < Z; k++) {
		p_a = &(spm_matrix->matrix1_A[0]);  /* point to the beginning of array A */

		_Pragma("loopbound min DIM max DIM")
		for(i = 0; i < X; i++) {
			p_b = &(spm_matrix->matrix1_B[k * Y]); /* take next column */

			*p_c = 0;
			_Pragma("loopbound min DIM max DIM")
			for(f = 0; f < Y; f++)    /* do multiply */
				*p_c += *p_a++ * *p_b++;

			p_c++;
		}
	}
}

static unsigned long long start_cycle, stop_cycle;
static unsigned long long return_cycles = 0;

int main(void)
{

#if(WCET)

	matrix1_pin_down();
	matrix1_main();

#else

	matrix1_pin_down();

	start_cycle = get_cpu_cycles();

	matrix1_main();

	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-CYCLE_CALIBRATION;

	print_benchmark(return_cycles, 0, 0);

#endif

	return 0;
}
