
/*
	This c file contains the forward declarations of functions
	used in benchmarking on hardware. 

	The initialization functions initializes the matrix values.

	The expected funtions generate the expected result (used for testing).

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License
	
 */

#include "matmul_hwa.h"

void matmul_init(mat_type mat_a[DIM][DIM], 
				 mat_type mat_b[DIM][DIM], 
				 mat_type sw_result[DIM][DIM]) {

	int i, j;

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {

			mat_a[i][j] = i + j + 1;
			mat_b[i][j] = i + j + 1 + DIM;
	      	sw_result[i][j] = 0;      				
		}
	}	
}

void matmul_init_spm(volatile _SPM mat_type (*mat_a)[DIM][DIM], 
					 volatile _SPM mat_type (*mat_b)[DIM][DIM], 
				 	 volatile _SPM mat_type (*sw_result)[DIM][DIM]) {
	int i, j;

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {

			(*mat_a)[i][j] = i + j + 1;
			(*mat_b)[i][j] = i + j + 1 + DIM;
	      	(*sw_result)[i][j] = 0;      				
		}
	}	
}

void matmul_init_uncached(volatile _UNCACHED mat_type (*mat_a)[DIM][DIM], 
					 volatile _UNCACHED mat_type (*mat_b)[DIM][DIM], 
				 	 volatile _UNCACHED mat_type (*sw_result)[DIM][DIM]) {
	int i, j;

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {

			(*mat_a)[i][j] = i + j + 1;
			(*mat_b)[i][j] = i + j + 1 + DIM;
	      	(*sw_result)[i][j] = 0;      				
		}
	}	
}


void matmul_expected(mat_type mat_a[DIM][DIM], 
					 mat_type mat_b[DIM][DIM], 
					 mat_type sw_result[DIM][DIM]) {
	int i, j, k;

	for(i = 0; i < DIM; i++) {
		for(j = 0; j < DIM; j++) {
			for(k = 0; k < DIM; k++) {
				sw_result[i][j] += mat_a[i][k] * mat_b[k][j];
        	}
    	}
	}		
}

void matmul_expected_spm(volatile _SPM mat_type (*mat_a)[DIM][DIM], 
					 	 volatile _SPM mat_type (*mat_b)[DIM][DIM], 
				 		 volatile _SPM mat_type (*sw_result)[DIM][DIM]) {
	int i, j, k;

	for(i = 0; i < DIM; i++) {
    	for(j = 0; j < DIM; j++) {
        	for(k = 0; k < DIM; k++) {
            	(*sw_result)[i][j] += (*mat_a)[i][k] * (*mat_b)[k][j];
        	}
    	}
	}		
}

void matmul_expected_uncached(volatile _UNCACHED mat_type (*mat_a)[DIM][DIM], 
					 	 volatile _UNCACHED mat_type (*mat_b)[DIM][DIM], 
				 		 volatile _UNCACHED mat_type (*sw_result)[DIM][DIM]) {
	int i, j, k;

	for(i = 0; i < DIM; i++) {
    	for(j = 0; j < DIM; j++) {
        	for(k = 0; k < DIM; k++) {
            	(*sw_result)[i][j] += (*mat_a)[i][k] * (*mat_b)[k][j];
        	}
    	}
	}		
}
