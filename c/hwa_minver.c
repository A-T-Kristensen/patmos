/*

    This program is part of the TACLeBench benchmark suite.
    Version V 1.x

    Name: minver

    Author: Sung-Soo Lim

    Function: Matrix inversion for 3x3 floating point matrix.

    Source: SNU-RT Benchmark Suite, via MRTC
           http://www.mrtc.mdh.se/projects/wcet/wcet_bench/minver/minver.c

    Changes: a brief summary of major functional changes (not formatting)

    License: may be used, modified, and re-distributed freely, but
             the SNU-RT Benchmark Suite must be acknowledged

*/

/*
    This program is derived from the SNU-RT Benchmark Suite for Worst
    Case Timing Analysis by Sung-Soo Lim

    Original source: Turbo C Programming for Engineering by Hyun Soo Ahn
*/

#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libminver/minver_init.h"
#include "libminver/minver.h"

int minver_main();
int main(void);

/*
    Test the hwa
*/

int minver_main()
{
  int i, j, k, err_cnt = 0;
  mat_type eps = 1.0e-6;

  volatile _IODEV mat_type** bank_ptr_array = (volatile _IODEV mat_type**) bank_ptrs(NBANKS);
  volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

  unsigned long long start_cycle, stop_cycle, return_cycles;  

  // divide factor
  int factor = NBANKS; // Division factor, a and b shares most banks // only use this if we have more than 1 bank
  int n = DIM; // the # columns
  int m = DIM; // the # rows
  int a_bank0 = 0; // Start bank

  mat_type minver_hw[DIM][DIM];
  mat_type minver_sw[DIM][DIM];
  mat_type minver_hw_i[DIM][DIM];
  mat_type minver_sw_i[DIM][DIM];

  set_minver(minver_hw, DIM);

  for ( i = 0; i < DIM; i++ ) {
    for ( j = 0; j < DIM; j++ ) {
      printf("%f ", minver_hw[i][j]);
    }
    printf("\n");    
  }     

  for ( i = 0; i < DIM; i++ ) {
    for ( j = 0; j < DIM; j++ ) {
    	minver_sw[i][j] = minver_hw[i][j];
    	minver_sw_i[i][j] = minver_hw[i][j];
    	minver_hw_i[i][j] = minver_hw[i][j];

    }
  }

  printf("Benchmarking with DIM=%d \n", DIM);

  start_cycle = get_cpu_cycles();

  minver_minver(minver_sw_i, DIM, eps);

  stop_cycle = get_cpu_cycles();
  return_cycles = stop_cycle-start_cycle-CYCLE_CALIBRATION;
  printf("#Cycles = %llu \n", return_cycles);   


  // Run accelerator
  start_cycle = get_cpu_cycles();

  for(i = 0; i < DIM*DIM; i++)
  {
      *(bank_ptr_array[NBANKS-1] + i) = *((&minver_hw_i[0][0]) + i);
  } 


  *hls_ptr = 1;

  // Poll status of HLS module
    
  while((*hls_ptr) != 1);

    // Read back the data  
    // For minver, it is distributed just as the written array  

    for(i = 0; i < DIM*DIM; i++)
    {
        *((&minver_hw_i[0][0]) + i) = *(bank_ptr_array[NBANKS-1] + i);
    } 

  stop_cycle = get_cpu_cycles();
  return_cycles = stop_cycle-start_cycle-CYCLE_CALIBRATION;
  printf("#Cycles = %llu \n", return_cycles);  

  for ( i = 0; i < DIM; i++ ) {
    for ( j = 0; j < DIM; j++ ) {
    	if(minver_hw_i[i][j] != minver_sw_i[i][j]) {
    		err_cnt++;
    	}
    }
  }

  for ( i = 0; i < DIM; i++ ) {
    for ( j = 0; j < DIM; j++ ) {
      printf("%f ", minver_hw_i[i][j]);
    }
    printf("\n");    
  }   

  if (err_cnt)
    printf("ERROR: %d\n", err_cnt);
  else
    printf("Test Passes:\n");  



  return err_cnt;
}

int main( void )
{
  int err_cnt = 0;

  err_cnt = minver_main();


  return 0;  

}
