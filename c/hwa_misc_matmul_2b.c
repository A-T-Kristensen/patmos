/*
  This is a minimal C program executed on the FPGA version of Patmos.
  An embedded test of a vivado hls module: Matrix multiplication 
  on an array of dimension DIM partitioned into 2 memory banks

  Author: Andreas T. Kristensen (s144026@student.dtu.dk)
  Copyright: BSD License
 */

#include "hwa_lib.h"

int main()  {

	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) 0xF0090000;
	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;    

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	mat_type mat_a[DIM][DIM];
	mat_type mat_b[DIM][DIM];
	mat_type sw_result[DIM][DIM], hw_result[DIM][DIM];
	mat_type in_bram[3*DIM][DIM]; // Data to be written to the bram.

	int err_cnt = 0;
	int i, j, k;

	// Initialize matrices

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			mat_a[i][j] = i+j+1;
			in_bram[i][j]  = mat_a[i][j];

			mat_b[i][j] = i+j+1+DIM;
			in_bram[i+DIM][j] = mat_b[i][j];
		}
	}

	// Generate the expected result
	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			sw_result[i][j] = 0;      	
			for(k = 0; k < DIM; k++) {
				sw_result[i][j] += mat_a[i][k] * mat_b[k][j];
			}
		}
	}	

   // Write to BRAM

   // Bank 1

	for(i = 0; i < 3*DIM*DIM/2; i++) {
		*(bank_ptr_array[0] + i) = *((&in_bram[0][0]) + i);
	}

	// Bank 2

	for(i = 0; i < DIM*DIM/2; i++) {
		*(bank_ptr_array[1] + i) = *((&in_bram[0][0]) + i + 3*DIM*DIM/2); 
	}   

	// Start HLS module
	
	*hls_ptr = 1;

	// Poll status of HLS module
	
	while((*hls_ptr) != 1);

	// Read back the data    

	for(i = 0; i < DIM*DIM; i++) {
		*((&hw_result[0][0]) + i)= *(bank_ptr_array[1] + i + 8); // Increment by 8 in memory bank 2
	}    
	
	// Check results

	puts("Checking results");	
	
	for(i = 0; i < DIM*DIM; i++) {
		printf("%f ", *((&hw_result[0][0]) + i) );        

		if((i+1) % DIM == 0) {
			printf("\n");
		}            

		if(*((&hw_result[0][0])+i) != *((&sw_result[0][0])+i)) {
			err_cnt++;	
		}	
	}

	printf("\n");    

	// We now continously loop, showing a pattern on the LEDS
	
	led_blink(err_cnt);

	return 0;
}
