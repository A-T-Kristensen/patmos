/*
	This c file contains the functions used to write to the BRAM 
	and generate pointers to the BRAMs.
	
	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License
	
 */

#include "hwa_bram.h"

void bank_ptrs(volatile _IODEV mat_type *bank_ptr_array[NBANKS], 
			   unsigned long nbanks) {

	int i;
	unsigned long bank_bits = (unsigned long) ceil(log2(NBANKS));

	for(i = 0; i < NBANKS; i++) {
		bank_ptr_array[i] = (volatile _IODEV mat_type *) 
							((i << (ADDR_BITS - bank_bits)) + BRAM_BASE);
	}
}

void write_array(mat_type array[ROWS][COLS], int n, int m, 
				 int factor, int array_bank0, 
				 volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					*(bank_ptr_array[i + array_bank0] + k + m * j / factor) 
						= array[j][k + i * n / factor];
				}
			}
		}		
	}

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					*(bank_ptr_array[i + array_bank0] + k + n * j) 
						= array[j + i * m / factor][k];
				}
			}
		}		
	}
}

void write_array_spm(volatile _SPM mat_type (*array)[ROWS][COLS], int n, 
					 int m, int factor, int array_bank0, 
					 volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					*(bank_ptr_array[i + array_bank0] + k + m * j / factor) 
						= (*array)[j][k + i * n / factor];
				}
			}
		}		
	} 

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					*(bank_ptr_array[i + array_bank0] + k + n*j) 
						= (*array)[j + i * m / factor][k];
				}
			}
		}		
	}
}

void write_array_uncached(volatile _UNCACHED mat_type (*array)[ROWS][COLS], 
						  int n, int m, int factor, int array_bank0, 
					 	  volatile _IODEV mat_type** bank_ptr_array, 
					 	  int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					*(bank_ptr_array[i+array_bank0] + k + m * j / factor) 
						= (*array)[j][k + i * n / factor];
				}
			}
		}		
	} 

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					*(bank_ptr_array[i + array_bank0] + k + n * j) 
						= (*array)[j + i * m / factor][k];
				}
			}
		}		
	}
}

void read_array(mat_type array[ROWS][COLS], int n, int m, int factor, 
				int array_bank0, volatile _IODEV mat_type** bank_ptr_array, 
				int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ){
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					array[j][k + i * n / factor] = *(bank_ptr_array[i + array_bank0] + k + m * j / factor);
				}
			}
		}		
	} 

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ){
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					array[j + i * m / factor][k] = *(bank_ptr_array[i + array_bank0] + k + n * j);
				}
			}
		}		
	}
}

void read_array_spm(volatile _SPM mat_type (*array)[ROWS][COLS], int n, 
					int m, int factor, int array_bank0, 
					volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ){
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					(*array)[j][k + i * n / factor] = *(bank_ptr_array[i + array_bank0] + k + m * j / factor);
				}
			}
		}
	}

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					(*array)[j + i * m / factor][k] = *(bank_ptr_array[i + array_bank0] + k + n*j) ;
				}
			}
		}
	}
}

void read_array_uncached(volatile _UNCACHED mat_type (*array)[ROWS][COLS], 
						 int n, int m, int factor, int array_bank0, 
					 	 volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					(*array)[j][k + i * n / factor] = *(bank_ptr_array[i+array_bank0] + k + m * j / factor);
				}
			}
		}		
	} 

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){

					(*array)[j + i * m / factor][k] = *(bank_ptr_array[i + array_bank0] + k + n * j);
				}
			}
		}		
	}
}

void write_vector(mat_type vec[], int length, int factor, int vec_bank0, 
				  volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){

			*(bank_ptr_array[i + vec_bank0] + j) = vec[j + i * length / factor];
		}
	}		
}

void write_vector_spm(volatile _SPM mat_type (*vec)[], int length, int factor, 
					  int vec_bank0, volatile _IODEV mat_type** bank_ptr_array){

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){

			*(bank_ptr_array[i + vec_bank0] + j) = (*vec)[j + i * length / factor];
		}
	}		
}

void write_vector_uncached(volatile _UNCACHED mat_type (*vec)[], int length, 
						   int factor, int vec_bank0, 
						   volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){

			*(bank_ptr_array[i + vec_bank0] + j) = (*vec)[j + i * length / factor];
		}
	}		
}

void read_vector(mat_type vec[], int length, int factor, int vec_bank0, 
				 volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){

			vec[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}		
}

void read_vector_spm(volatile _SPM mat_type (*vec)[], int length, 
					 int factor, int vec_bank0, 
				  	 volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ){
		for(j = 0; j < length/factor; j++){

			(*vec)[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}		
}

void read_vector_uncached(volatile _UNCACHED  mat_type (*vec)[], int length, 
						  int factor, int vec_bank0, 
				  		  volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){

			(*vec)[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}		
}