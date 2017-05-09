/*
	This c file contains the functions used to write to the BRAM 
	and generate pointers to the BRAMs.
	
	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: DTU, BSD License
	
 */

#include "hwa_bram.h"

/*
	NAME: bank_ptrs()

	PARAMETERS:
		* nbanks: The number of memory banks

	RETURNS: An array of pointers to the BRAMs

	DESCRIPTION: bank_ptrs() generates an array of pointers to the bram blocks.
	
 */


volatile _IODEV unsigned long** bank_ptrs(unsigned long nbanks) {

	int i;
	unsigned long bank_bits = (unsigned long) ceil(log2(nbanks));

	volatile _IODEV unsigned long** bank_ptr_array = (volatile _IODEV unsigned long**) malloc(bank_bits*sizeof(unsigned long*));

	for(i = 0; i < nbanks; i++) {
		bank_ptr_array[i] = (volatile _IODEV unsigned long *) ((i << (ADDR_BITS - bank_bits)) + BRAM_BASE);
	}

	return bank_ptr_array;
}

/*
	NAME: write_array()

	PARAMETERS:
		* array: the array to be written into the BRAM.
		* n: the # columns
		* m: the # rows
		* factor: Partition factor (partinioned if factor > 1)
		* array_bank0: First index into bank_ptr_array
		* bank_ptr_array: Array of pointers to the bram blocks
		* wr_dim: Dimension of array partitioning (partinioned if factor > 1)

	RETURNS: void

	DESCRIPTION: write_array() writes an array to BRAM blocks.
				 If factor > 1, array is partitioned.
	
 */

void write_array(mat_type array[DIM][DIM], int n, int m, int factor, int array_bank0, 
				 volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					*(bank_ptr_array[i + array_bank0] + k + m * j / factor) = array[j][k + i * n / factor];
				}
			}
		}		
	} 

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					*(bank_ptr_array[i + array_bank0] + k + n * j) = array[j + i * m / factor][k];
				}
			}
		}		
	}
}

void write_array_spm(volatile _SPM mat_type (*array)[DIM][DIM], int n, 
					 int m, int factor, int array_bank0, 
				     volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					*(bank_ptr_array[i + array_bank0] + k + m * j / factor) = (*array)[j][k + i * n / factor];
				}
			}
		}		
	} 

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					*(bank_ptr_array[i + array_bank0] + k + n*j) = (*array)[j + i * m / factor][k];
				}
			}
		}		
	}
   	
}

void write_array_uncached(volatile _UNCACHED mat_type (*array)[DIM][DIM], int n, 
					 int m, int factor, int array_bank0, 
				     volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					*(bank_ptr_array[i+array_bank0] + k + m * j / factor) = (*array)[j][k + i * n / factor];
				}
			}
		}		
	} 

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					*(bank_ptr_array[i + array_bank0] + k + n * j) = (*array)[j + i * m / factor][k];
				}
			}
		}		
	}
}

void read_array(mat_type array[DIM][DIM], int n, int m, int factor, int array_bank0, 
				 volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m; j++){
				for(k = 0; k < n/factor; k++){
					array[j][k + i * n / factor] = *(bank_ptr_array[i + array_bank0] + k + m * j / factor);
				}
			}
		}		
	} 

	else if (wr_dim == 1) {
		for(i = 0; i < factor; i++ ) {
			for(j = 0; j < m/factor; j++){
				for(k = 0; k < n; k++){
					array[j + i * m / factor][k] = *(bank_ptr_array[i + array_bank0] + k + n * j);
				}
			}
		}		
	}
}

void read_array_spm(volatile _SPM mat_type (*array)[DIM][DIM], int n, 
					 int m, int factor, int array_bank0, 
				     volatile _IODEV mat_type** bank_ptr_array, int wr_dim){

	int i, j, k;	

	if (wr_dim == 2) {
		for(i = 0; i < factor; i++ ) {
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

void read_array_uncached(volatile _UNCACHED mat_type (*array)[DIM][DIM], int n, 
					 int m, int factor, int array_bank0, 
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

void write_vector(mat_type vec[DIM], int length, int factor, int vec_bank0, 
				  volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){
			*(bank_ptr_array[i + vec_bank0] + j) = vec[j + i * length / factor];
		}
	}		
}

void write_vector_spm(volatile _SPM mat_type (*vec)[DIM], int length, int factor, int vec_bank0, 
				  volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){
			*(bank_ptr_array[i + vec_bank0] + j) = (*vec)[j + i * length / factor];
		}
	}		
}

void write_vector_uncached(volatile _UNCACHED mat_type (*vec)[DIM], int length, int factor, int vec_bank0, 
				  volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){
			*(bank_ptr_array[i + vec_bank0] + j) = (*vec)[j + i * length / factor];
		}
	}		
}


void read_vector(mat_type vec[DIM], int length, int factor, int vec_bank0, 
				  volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){
			vec[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}		
}

void read_vector_spm(volatile _SPM mat_type (*vec)[DIM], int length, int factor, int vec_bank0, 
				  volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){
			(*vec)[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}		
}


void read_vector_uncached(volatile _UNCACHED  mat_type (*vec)[DIM], int length, int factor, int vec_bank0, 
				  volatile _IODEV mat_type** bank_ptr_array) {

	int i, j;

	for(i = 0; i < factor; i++ ) {
		for(j = 0; j < length/factor; j++){
			(*vec)[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}		
}