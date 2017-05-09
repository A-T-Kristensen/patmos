
#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

//#define mat_type int
//typedef float mat_type;
//#define mat_type float

void filterbank_init( void );
int filterbank_main( void );
int filterbank_return( void );
void filterbank_core_hwa( mat_type r[ 256 ],
    mat_type y[ 256 ],
    mat_type H[ 8 ][ 32 ],
    mat_type F[ 8 ][ 32 ] );

void filterbank_core_test( mat_type r[ 256 ],
    mat_type y[ 256 ],
    mat_type H[ 8 ][ 32 ],
    mat_type F[ 8 ][ 32 ] );

void filter_init(mat_type r[256], mat_type H[8][32], mat_type F[8][32]);

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

void filterbank_core_test( mat_type r[ 256 ],
		mat_type y[ 256 ],
		mat_type H[ 8 ][ 32 ],
		mat_type F[ 8 ][ 32 ] )
{
  int i, j, k;

  for ( i = 0; i < 256; i++ ){
	    y[ i ] = 0;
  }

    for ( i = 0; i < 8; i++ ) {
        mat_type Vect_H[ 256 ]; /* (output of the H) */
        mat_type Vect_Dn[ ( int ) 256 / 8 ]; /* output of the down sampler; */
        mat_type Vect_Up[ 256 ]; /* output of the up sampler; */
        mat_type Vect_F[ 256 ]; /* this is the output of the */

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


void filter_init(mat_type r[256], mat_type H[8][32], mat_type F[8][32]) {

    int i, j;

    for ( i = 0; i < 256; i++ ){
        r[i] = i + 1;
    }

    for ( i = 0; i < 32; i++ ) {
        for ( j = 0; j < 8; j++ ) {
            H[j][i] = i * 32 + j * 8 + j + i + j + 1;
            F[j][i] = i * j + j * j + j + i;
        }
    }

}

int filterbank_main( void ) {
    mat_type r[ 256 ] = {0};
    mat_type y_sw[ 256 ] = {0};
    mat_type y_hw[ 256 ] = {0};
    mat_type H[ 8 ][ 32 ] = {0};
    mat_type F[ 8 ][ 32 ] = {0};
    int err_cnt = 0;

    volatile _IODEV mat_type** bank_ptr_array = (volatile _IODEV mat_type**) bank_ptrs(NBANKS);
    volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;     

    int i, j;

    unsigned long long start_compute, stop_compute, return_compute;  
    unsigned long long start_transfer, stop_transfer, return_transfer;   

    // Initialize

    filter_init(r, H, F);

    // Initialize  
    filterbank_init();

    // Calculate software values
    while ( filterbank_numiters-- > 0 ){
        filterbank_core_test( r, y_sw, H, F );    
    }

    // Re initialize for HwA test
    filterbank_init();

    // Move data into hardware

    start_transfer = get_cpu_cycles();

    write_vector(r, DIM, 1, 0, bank_ptr_array);
    write_vector(y_hw, DIM, 1, 1, bank_ptr_array);
    write_array(H, 32, 8, 1, 2, bank_ptr_array, 1);
    write_array(F, 32, 8, 1, 3, bank_ptr_array, 1);

    stop_transfer = get_cpu_cycles();
    return_transfer = stop_transfer-start_transfer-CYCLE_CALIBRATION; 

    start_compute = get_cpu_cycles();     

    while ( filterbank_numiters-- > 0 ) {

        // Start HLS module

        *hls_ptr = 1;
        *hls_ptr = 0;  

        // Poll status of HLS module

        while((*hls_ptr) != 1);

    }

    stop_compute = get_cpu_cycles();
    return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;         

    start_transfer = get_cpu_cycles();        

    read_vector(y_hw, DIM, 1, 1, bank_ptr_array);

    stop_transfer = get_cpu_cycles();
    return_transfer += stop_transfer-start_transfer-CYCLE_CALIBRATION;

  // Compare results

    for(i = 0; i < 256; i++){
        if(y_sw[i] != y_hw[i]) {
            err_cnt++;
        }
    }

    print_benchmark(return_compute, return_transfer);

    return err_cnt;

}

/*
  Main function
*/

int main( void ){

    int err_cnt;

    err_cnt = filterbank_main();

    return err_cnt;
}
