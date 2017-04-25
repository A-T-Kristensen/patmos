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

#include <machine/rtc.h> // Gives us get_cpu_cycles
#include <machine/spm.h> // Defines _SPM
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.
#include <stdio.h>

#define X 4 /* first dimension of array A */
#define Y 4 /* second dimension of array A, first dimension of array B */
#define Z 4 /* second dimension of array B */

/*
  Forward declaration of functions
*/

void matrix1_pin_down(void);
void matrix1_main( void );
int main( void );


/*
  Declaration of global variables
*/

struct matrix {
    float matrix1_A[X * Y];
    float matrix1_B[Y * Z];
    float matrix1_C[X * Z]; 
};

volatile _SPM struct matrix *spm_matrix = (volatile _SPM struct matrix *) SPM_BASE;

/*
  Initialization functions
*/

void matrix1_pin_down(void)
{
  int i;
  volatile float x = 1;

  _Pragma( "loopbound min 100 max 100" )
  for ( i = 0 ; i < X * Y; i++ )
    spm_matrix->matrix1_A[i] = x ;

  _Pragma( "loopbound min 100 max 100" )
  for ( i = 0 ; i < Y * Z ; i++ )
    spm_matrix->matrix1_B[i] = x ;

  _Pragma( "loopbound min 100 max 100" )
  for ( i = 0 ; i < X * Z ; i++ )
    spm_matrix->matrix1_C[i] = 0 ;
}


/*
  Return function
*/

int matrix1_return( void )
{
	int i;
	int checksum = 0;

	  _Pragma( "loopbound min 100 max 100" )
	  for ( i = 0; i <= X*Z; i++ )
		  checksum += spm_matrix->matrix1_C[i];

	  return ( checksum ==  1000 ? 0 : -1 );
}


/*
  Main functions
*/

void _Pragma ( "entrypoint" ) matrix1_main( void )
{
  volatile _SPM float *p_a = &(spm_matrix->matrix1_A[0]);
  volatile _SPM float *p_b = &(spm_matrix->matrix1_B[0]);
  volatile _SPM float *p_c = &(spm_matrix->matrix1_C[0]);

  int f, i, k;

  _Pragma( "loopbound min 10 max 10" )
  for ( k = 0; k < Z; k++ ) {
    p_a = &(spm_matrix->matrix1_A[0]);                /* point to the beginning of array A */

    _Pragma( "loopbound min 10 max 10" )
    for ( i = 0; i < X; i++ ) {
      p_b = &(spm_matrix->matrix1_B[k * Y]);          /* take next column */

      *p_c = 0;
      _Pragma( "loopbound min 10 max 10" )
      for ( f = 0; f < Y; f++ ) /* do multiply */
        *p_c += *p_a++ * *p_b++;

      p_c++;
    }
  }
}


int main( void )
{
  static unsigned long long start_cycle, stop_cycle, calibration; 
  static unsigned long long return_cycles = 0;    

  start_cycle = get_cpu_cycles();
  stop_cycle = get_cpu_cycles();
  calibration = stop_cycle-start_cycle;

  printf("%llu \n", calibration);

  matrix1_pin_down();

  start_cycle = get_cpu_cycles();

  matrix1_main();

  stop_cycle = get_cpu_cycles();
  return_cycles = stop_cycle-start_cycle-calibration;
  printf("%llu \n", return_cycles);   




  return matrix1_return();
}
