
#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

//#define vec_type int
typedef float vec_type;
//#define vec_type float

void filterbank_init( void );
void filterbank_main( void );
int filterbank_return( void );
void filterbank_core_hwa( vec_type r[ 256 ],
    vec_type y[ 256 ],
    vec_type H[ 8 ][ 32 ],
    vec_type F[ 8 ][ 32 ] );

void filterbank_core_test( vec_type r[ 256 ],
    vec_type y[ 256 ],
    vec_type H[ 8 ][ 32 ],
    vec_type F[ 8 ][ 32 ] );


/*
  Declaration of global variables
*/

static int filterbank_return_value;
static int filterbank_numiters;

void filterbank_init( void )
{
  filterbank_numiters = 2;
}


int filterbank_return( void )
{
  return filterbank_return_value;
}

/*
  Core benchmark functions for test
*/


void filterbank_core_test( vec_type r[ 256 ],
		vec_type y[ 256 ],
		vec_type H[ 8 ][ 32 ],
		vec_type F[ 8 ][ 32 ] )
{
  int i, j, k;

  for ( i = 0; i < 256; i++ ){
	    y[ i ] = 0;
  }

  for ( i = 0; i < 8; i++ ) {
	  vec_type Vect_H[ 256 ]; /* (output of the H) */
	  vec_type Vect_Dn[ ( int ) 256 / 8 ]; /* output of the down sampler; */
	  vec_type Vect_Up[ 256 ]; /* output of the up sampler; */
	  vec_type Vect_F[ 256 ]; /* this is the output of the */

    /* convolving H */
    for ( j = 0; j < 256; j++ ) {
        Vect_H[ j ] = 0;
      for ( k = 0; ( ( k < 32 ) & ( ( j - k ) >= 0 ) ); k++ ){
          Vect_H[ j ] += H[ i ][ k ] * r[ j - k ];
    	  }
      }

    /* Down Sampling */
    for ( j = 0; j < 256 / 8; j++ ){
        Vect_Dn[ j ] = Vect_H[ j * 8 ];

    }
    /* Up Sampling */
    for ( j = 0; j < 256; j++ ){
        Vect_Up[ j ] = 0;

    }
    for ( j = 0; j < 256 / 8; j++ ){
        Vect_Up[ j * 8 ] = Vect_Dn[ j ];
    }
    /* convolving F */
    for ( j = 0; j < 256; j++ ) {
      Vect_F[ j ] = 0;
      for ( k = 0; ( ( k < 32 ) & ( ( j - k ) >= 0 ) ); k++ ){
          Vect_F[ j ] += F[ i ][ k ] * Vect_Up[ j - k ];
    	  }
      }

    /* adding the results to the y matrix */

    for ( j = 0; j < 256; j++ ){
        y[ j ] += Vect_F[ j ];
    }
    }
}


void filterbank_main( void )
{
	vec_type r[ 256 ] = {0};
	vec_type y_sw[ 256 ] = {0};
	vec_type y_hw[ 256 ] = {0};
	vec_type H[ 8 ][ 32 ] = {0};
	vec_type F[ 8 ][ 32 ] = {0};
  int err_cnt = 0;

  volatile _IODEV mat_type** bank_ptr_array = (volatile _IODEV mat_type**) bank_ptrs(NBANKS);
  volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;     

  int i, j;

  unsigned long long start_cycle, stop_cycle, calibration;  
  unsigned long long return_cycles = 0;   

  start_cycle = get_cpu_cycles();
  stop_cycle = get_cpu_cycles();
  calibration = stop_cycle-start_cycle;

  printf("%llu \n", calibration);  

  // Initialize

  for ( i = 0; i < 256; i++ ){
	    r[ i ] = i + 1;
  }
  for ( i = 0; i < 32; i++ ) {

    for ( j = 0; j < 8; j++ ) {
      H[ j ][ i ] = i * 32 + j * 8 + j + i + j + 1;
      F[ j ][ i ] = i * j + j * j + j + i;
    }
  }

  // Test software
  filterbank_init();

  start_cycle = get_cpu_cycles();


  while ( filterbank_numiters-- > 0 ){
    filterbank_core_test( r, y_sw, H, F );    
  }

  stop_cycle = get_cpu_cycles();
  return_cycles = stop_cycle-start_cycle-calibration;
  printf("%llu \n", return_cycles);      


  filterbank_init();

  // Test hardware

  // Move data into hardware

  // r

  start_cycle = get_cpu_cycles();  

    for(i = 0; i < 256; i++)
    {
        *(bank_ptr_array[0] + i) = *((&r[0]) + i);
    }

  // y

    for(i = 0; i < 256; i++)
    {
        *(bank_ptr_array[1] + i) = *((&y_hw[0]) + i);
    }

// H    

    for(i = 0; i < 8*32; i++)
    {
        *(bank_ptr_array[2] + i) = *((&H[0][0]) + i);
    }

  // F

    for(i = 0; i < 8*32; i++)
    {
        *(bank_ptr_array[3] + i) = *((&F[0][0]) + i);
    }    


  while ( filterbank_numiters-- > 0 ) {

    // Start HLS module
  
  *hls_ptr = 1;
  *hls_ptr = 0;  

  // Poll status of HLS module
    
    while((*hls_ptr) != 1);

  }

    for(i = 0; i < 256; i++)
    {
        *((&y_hw[0]) + i)= *(bank_ptr_array[1] + i); 
    }   

  stop_cycle = get_cpu_cycles();
  return_cycles = stop_cycle-start_cycle-calibration;
  printf("%llu \n", return_cycles);      

  // Compare results

  for(i = 0; i < 256; i++){
    if(y_sw[i] != y_hw[i]) {
      err_cnt++;
    }
  }

  led_blink(err_cnt);

}

/*
  Main function
*/

int main( void )
{

  filterbank_main();

  return 0;
}
