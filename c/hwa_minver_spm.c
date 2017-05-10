/*
  This c file contains the main benchmark program
  for matrix inversion.

  It is based on the "minver" benchmark from the TACLeBench 
  benchmark suite (author Sung-Soo Lim.

  Author: Andreas T. Kristensen (s144026@student.dtu.dk)
  Copyright: BSD License
  
 */

/*
    This program is derived from the SNU-RT Benchmark Suite for Worst
    Case Timing Analysis by Sung-Soo Lim

    Original source: Turbo C Programming for Engineering by Hyun Soo Ahn
 */

#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"
#include "libminver/minver_init.h"
#include "libminver/minver.h"

int minver_main();
int main(void);

struct matrix {
    mat_type hw_result[DIM][DIM]; 
    mat_type sw_result[DIM][DIM]; 
};
volatile _SPM struct matrix *spm_matrix = (volatile _SPM struct matrix *) SPM_BASE;


int minver_minver_spm(volatile _SPM mat_type (*minver_a)[ DIM ][ DIM ], int side, mat_type eps ) {

  int work[ 500 ], i, j, k, iw;
  int r = 0;
  mat_type w, wmax, pivot, api, w1;
  mat_type minver_det;


  if ( side < 2 || side > 500 || eps <= 0.0 )
    return ( 999 );
  w1 = 1.0;
  _Pragma( "loopbound min 3 max 3" )
  for ( i = 0; i < side; i++ )
    work[ i ] = i;
  _Pragma( "loopbound min 3 max 3" )
  for ( k = 0; k < side; k++ ) {
    wmax = 0.0;
    _Pragma( "loopbound min 1 max 3" )
    for ( i = k; i < side; i++ ) {
      w = minver_fabs( (*minver_a)[ i ][ k ] );
      if ( w > wmax ) {
        wmax = w;
        r = i;
      }
    }
    pivot = (*minver_a)[ r ][ k ];
    api = minver_fabs( pivot );
    if ( api <= eps ) {
      minver_det = w1;
      return ( 1 );
    }
    w1 *= pivot;
    if ( r != k ) {
      w1 = -w;
      iw = work[ k ];
      work[ k ] = work[ r ];
      work[ r ] = iw;
      _Pragma( "loopbound min 3 max 3" )
      for ( j = 0; j < side; j++ ) {
        w = (*minver_a)[ k ][ j ];
        (*minver_a)[ k ][ j ] = (*minver_a)[ r ][ j ];
        (*minver_a)[ r ][ j ] = w;
      }
    }
    _Pragma( "loopbound min 3 max 3" )
    for ( i = 0; i < side; i++ )
      (*minver_a)[ k ][ i ] /= pivot;
    _Pragma( "loopbound min 3 max 3" )
    for ( i = 0; i < side; i++ ) {
      if ( i != k ) {
        w = (*minver_a)[ i ][ k ];
        if ( w != 0.0 ) {
          _Pragma( "loopbound min 3 max 3" )
          for ( j = 0; j < side; j++ ) {
            if ( j != k ) (*minver_a)[ i ][ j ] -= w * (*minver_a)[ k ][ j ];
          }
          (*minver_a)[ i ][ k ] = -w / pivot;

        }
      }
    }
    (*minver_a)[ k ][ k ] = 1.0 / pivot;
  }
  for ( i = 0; i < side; ) {
    /*  The following redundant statement is inserted due to limitations of
        WCC's flow fact manager. It is required in order to have the flow
        fact pragma below uniquely attached to the while(1) loop.
    */
    i = i;
    while ( 1 ) {
      k = work[ i ];
      if ( k == i ) break;
      iw = work[ k ];
      work[ k ] = work[ i ];
      work[ i ] = iw;
      for ( j = 0; j < side; j++ ) {
        w = (*minver_a) [k ][ i ];
        (*minver_a)[ k ][ i ] = (*minver_a)[ k ][ k ];
        (*minver_a)[ k ][ k ] = w;
      }
    }
    i++;
  }
  minver_det = w1;
  return ( 0 );

}

int minver_main() {

    int i, j, k, err_cnt = 0;
    mat_type eps = 1.0e-6;

    unsigned long long start_compute, stop_compute, return_compute;  
    unsigned long long start_transfer, stop_transfer, return_transfer;     

    volatile _IODEV mat_type *bank_ptr_array[NBANKS];
    bank_ptrs(bank_ptr_array, NBANKS);

    volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

    set_minver_spm(&spm_matrix->hw_result);

    printf("Benchmarking \n");

    for ( i = 0; i < DIM; i++ ) {
        for ( j = 0; j < DIM; j++ ) {
          	spm_matrix->sw_result[i][j] = spm_matrix->hw_result[i][j];
        }
    }
    // Compute expected results

    minver_minver_spm(&spm_matrix->sw_result, DIM, eps );

    // Run accelerator

    start_transfer = get_cpu_cycles();

    #if(NBANKS>1)

    write_array_spm(&spm_matrix->hw_result, DIM, DIM, NBANKS, 0, bank_ptr_array, 2);

    #else

    write_array_spm(&spm_matrix->hw_result, DIM, DIM, NBANKS, 0, bank_ptr_array, 1);    

    #endif

    stop_transfer = get_cpu_cycles();
    return_transfer = stop_transfer-start_transfer-CYCLE_CALIBRATION;

    // Poll status of HLS module    

    *hls_ptr = 1;

    start_compute = get_cpu_cycles();    

    while((*hls_ptr) != 1);

    stop_compute = get_cpu_cycles();
    return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;    

    start_transfer = get_cpu_cycles();    

    #if(NBANKS>1)

    read_array_spm(&spm_matrix->hw_result, DIM, DIM, NBANKS, 0, bank_ptr_array, 2);

    #else

    read_array_spm(&spm_matrix->hw_result, DIM, DIM, NBANKS, 0, bank_ptr_array, 1);    

    #endif   

    stop_transfer = get_cpu_cycles();
    return_transfer += stop_transfer-start_transfer-CYCLE_CALIBRATION;

    err_cnt = compare_arrays_spm(&spm_matrix->hw_result, &spm_matrix->sw_result);

    print_benchmark(return_compute, return_transfer);

/*    printf("%d\n", err_cnt);

        printf("\n");    

    for ( i = 0; i < DIM; i++ ) {
        for ( j = 0; j < DIM; j++ ) {
            printf("%f ", spm_matrix->hw_result[i][j]);
        }
        printf("\n");
    }        

    for ( i = 0; i < DIM; i++ ) {
        for ( j = 0; j < DIM; j++ ) {
            printf("%f ", spm_matrix->sw_result[i][j]);
        }
        printf("\n");
    }  

*/
    return err_cnt;
}

int main( void ) {

    return (minver_main());  

}
