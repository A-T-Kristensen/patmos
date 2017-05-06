/*
	This header file contains the forward declarations and
	documentation for the functions in hwa_bram.c
	
	These functions are used to write to the BRAM and generate
	pointers to the BRAMs.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: DTU, BSD License
	
 */

#ifndef HWA_BRAM_H_
#define HWA_BRAM_H_

#include "hwa_lib.h"

/*
	NAME: bank_ptrs()

	PARAMETERS:
		* nbanks: The number of memory banks

	RETURNS: An array of pointers to the BRAMs

	DESCRIPTION: bank_ptrs() generates an array of pointers to the bram blocks.
	
 */

volatile _IODEV unsigned long** bank_ptrs(unsigned long nbanks);


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
				 volatile _IODEV mat_type** bank_ptr_array, int wr_dim);

void write_array_spm(volatile _SPM mat_type (*array)[DIM][DIM], int n, 
					 int m, int factor, int array_bank0, 
				     volatile _IODEV mat_type** bank_ptr_array, int wr_dim);

void write_array_uncached(volatile _UNCACHED mat_type (*array)[DIM][DIM], int n, 
					 int m, int factor, int array_bank0, 
				     volatile _IODEV mat_type** bank_ptr_array, int wr_dim);

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

void read_array(mat_type array[DIM][DIM], int n, int m, int factor, int array_bank0, 
				 volatile _IODEV mat_type** bank_ptr_array, int wr_dim);

void read_array_spm(volatile _SPM mat_type (*array)[DIM][DIM], int n, 
					 int m, int factor, int array_bank0, 
				     volatile _IODEV mat_type** bank_ptr_array, int wr_dim);

void read_array_uncached(volatile _UNCACHED mat_type (*array)[DIM][DIM], int n, 
					 int m, int factor, int array_bank0, 
				     volatile _IODEV mat_type** bank_ptr_array, int wr_dim);


#endif /* __HWA_BRAM_H__ */
