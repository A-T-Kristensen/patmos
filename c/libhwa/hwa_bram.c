/*
	This c file contains the functions used to write to the BRAM
	and generate pointers to the BRAMs.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License

 */

#include "hwa_bram.h"

void bank_ptrs(volatile _IODEV mat_type *bank_ptr_array[NBANKS],
			   unsigned long nbanks)
{

	int i;
	unsigned long bank_bits = (unsigned long) ceil(log2(NBANKS));

	_Pragma("loopbound min NBANKS max NBANKS")
	for(i = 0; i < NBANKS; i++) {
		bank_ptr_array[i] = (volatile _IODEV mat_type *)
							((i << (ADDR_BITS - bank_bits)) + BRAM_BASE);
	}
}

void write_array(mat_type *array, int n, int m, 
				 int factor, int array_bank0, int wr_dim)
{

	int i, j, k;

	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) BRAM_BASE;
	volatile _IODEV mat_type *bram_ptr_write = (volatile _IODEV mat_type *) BRAM_BASE;

	// Set up MCU for A
	// array_vect = 0, wr_dim, DIM, DIM, factor, start_bank = 0
	*(bram_ptr) = (0 << 30) | (wr_dim << 28) | (DIM << 18)
				  | (DIM << 8) | (factor << 4) | array_bank0;

	_Pragma("loopbound min SIZE max SIZE")
	for(i = 0; i < m*n; i++) {
		*(bram_ptr_write + 1) = *(array + i);
	}
}

void write_array_spm(volatile _SPM mat_type *array, int n,
					 int m, int factor, int array_bank0, int wr_dim)
{

	int i, j, k;

	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) BRAM_BASE;
	volatile _IODEV mat_type *bram_ptr_write = (volatile _IODEV mat_type *) BRAM_BASE;

	// Set up MCU for A
	// array_vect = 0, wr_dim, DIM, DIM, factor, start_bank = 0
	*(bram_ptr) = (0 << 30) | (wr_dim << 28) | (DIM << 18)
				  | (DIM << 8) | (factor << 4) | array_bank0;

	_Pragma("loopbound min SIZE max SIZE")
	for(i = 0; i < m*n; i++) {
		*(bram_ptr_write + 1) = *(array + i);
	}
}

void read_array(mat_type *array, int n, int m, 
				int factor, unsigned int array_bank0)
{

	int i, j, k;
	volatile _IODEV mat_type *bram_ptr_read = (volatile _IODEV mat_type *) array_bank0;

	_Pragma("loopbound min SIZE max SIZE")
	for(i = 0; i < m*n; i++) {
		*(array + i) = *(bram_ptr_read + i) ;
	}
}

void read_array_spm(volatile _SPM mat_type *array, int n,
					int m, int factor, unsigned int array_bank0)
{

	int i, j, k;
	volatile _IODEV mat_type *bram_ptr_read = (volatile _IODEV mat_type *) array_bank0;

	_Pragma("loopbound min SIZE max SIZE")
	for(i = 0; i < m*n; i++) {
		*(array + i) = *(bram_ptr_read + i) ;
	}
}

void write_vector(mat_type vec[], int length, int factor, int vec_bank0,
				  volatile _IODEV mat_type** bank_ptr_array)
{

	int i, j;

	_Pragma("loopbound min VEC_WR_FACTOR max VEC_WR_FACTOR")
	for(i = 0; i < factor; i++) {
		_Pragma("loopbound min VEC_WR_DIV max VEC_WR_DIV")
		for(j = 0; j < length/factor; j++) {

			*(bank_ptr_array[i + vec_bank0] + j) = vec[j + i * length / factor];
		}
	}
}

void write_vector_spm(volatile _SPM mat_type *vec, int length, int factor,
					  int vec_bank0)
{

	int i, j;

	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) BRAM_BASE;
	volatile _IODEV mat_type *bram_ptr_write = (volatile _IODEV mat_type *) BRAM_BASE;

	// Set up MCU for A
	// array_vect = 0, wr_dim, DIM, DIM, factor, start_bank = 0
	*(bram_ptr) = (1 << 30) | (0 << 28) | (length << 18)
				  | (length << 8) | (factor << 4) | vec_bank0;

	_Pragma("loopbound min VECSIZE max VECSIZE")
	for(i = 0; i < length; i++) {
		*(bram_ptr_write + 1) = *(vec + i);
	}
}

void read_vector(mat_type vec[], int length, int factor, int vec_bank0,
				 volatile _IODEV mat_type** bank_ptr_array)
{

	int i, j;

	_Pragma("loopbound min VEC_RD_FACTOR max VEC_RD_FACTOR")
	for(i = 0; i < factor; i++) {
		_Pragma("loopbound min VEC_RD_DIV max VEC_RD_DIV")
		for(j = 0; j < length/factor; j++) {

			vec[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}
}

void read_vector_spm(volatile _SPM mat_type *vec, int length,
					 int factor, int vec_bank0)
{

	int i, j;

	volatile _IODEV mat_type *bram_ptr_read = (volatile _IODEV mat_type *) vec_bank0;

	_Pragma("loopbound min VECSIZE max VECSIZE")
	for(i = 0; i < length; i++) {
		*(vec + i) = *(bram_ptr_read + i) ;
	}

}
