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

void write_array(mat_type array[ROWS][COLS], int n, int m,
				 int factor, int array_bank0,
				 volatile _IODEV mat_type** bank_ptr_array, int wr_dim)
{

	int i, j, k;

	if(wr_dim == 2) {
		_Pragma("loopbound min ARRAY_WR_FACTOR max ARRAY_WR_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ROWS max ROWS")								
			for(j = 0; j < m; j++) {
				_Pragma("loopbound min ARRAY_WR_DIV max ARRAY_WR_DIV")				
				for(k = 0; k < n/factor; k++) {
					*(bank_ptr_array[i + array_bank0] 
						+ k + m * j / factor)
						= array[j][k + i * n / factor];
				}
			}
		}
	}

	else if(wr_dim == 1) {
		_Pragma("loopbound min ARRAY_WR_FACTOR max ARRAY_WR_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ARRAY_WR_DIV max ARRAY_WR_DIV")						
			for(j = 0; j < m/factor; j++) {
			_Pragma("loopbound min COLS max COLS")
				for(k = 0; k < n; k++) {
					*(bank_ptr_array[i + array_bank0] + k + n * j)
						= array[j + i * m / factor][k];
				}
			}
		}
	}
}

void write_array_spm(volatile _SPM mat_type(*array)[ROWS][COLS], int n,
					 int m, int factor, int array_bank0,
					 volatile _IODEV mat_type** bank_ptr_array, int wr_dim)
{

	int i, j, k;

	if(wr_dim == 2) {
		_Pragma("loopbound min ARRAY_WR_FACTOR max ARRAY_WR_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ROWS max ROWS")								
			for(j = 0; j < m; j++) {
				_Pragma("loopbound min ARRAY_WR_DIV max ARRAY_WR_DIV")				
				for(k = 0; k < n/factor; k++) {
					*(bank_ptr_array[i + array_bank0] + k + m * j / factor)
						= (*array)[j][k + i * n / factor];
				}
			}
		}
	}

	else if(wr_dim == 1) {
		_Pragma("loopbound min ARRAY_WR_FACTOR max ARRAY_WR_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ARRAY_WR_DIV max ARRAY_WR_DIV")						
			for(j = 0; j < m/factor; j++) {
			_Pragma("loopbound min COLS max COLS")
				for(k = 0; k < n; k++) {
					*(bank_ptr_array[i + array_bank0] 
						+ k + n*j)
						= (*array)[j + i * m / factor][k];
				}
			}
		}
	}
}

void write_array_uncached(volatile _UNCACHED mat_type(*array)[ROWS][COLS],
						  int n, int m, int factor, int array_bank0,
						  volatile _IODEV mat_type** bank_ptr_array,
						  int wr_dim)
{

	int i, j, k;

	if(wr_dim == 2) {
		_Pragma("loopbound min ARRAY_WR_FACTOR max ARRAY_WR_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ROWS max ROWS")
			for(j = 0; j < m; j++) {
				_Pragma("loopbound min ARRAY_WR_DIV max ARRAY_WR_DIV")				
				for(k = 0; k < n/factor; k++) {
					*(bank_ptr_array[i+array_bank0] 
						+ k + m * j / factor)
						= (*array)[j][k + i * n / factor];
				}
			}
		}
	}

	else if(wr_dim == 1) {
		_Pragma("loopbound min ARRAY_WR_FACTOR max ARRAY_WR_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ARRAY_WR_DIV max ARRAY_WR_DIV")			
			for(j = 0; j < m/factor; j++) {
			_Pragma("loopbound min COLS max COLS")
				for(k = 0; k < n; k++) {
					*(bank_ptr_array[i + array_bank0] 
						+ k + n * j)
						= (*array)[j + i * m / factor][k];
				}
			}
		}
	}
}

void read_array(mat_type array[ROWS][COLS], int n, int m, int factor,
				int array_bank0, volatile _IODEV mat_type** bank_ptr_array,
				int wr_dim)
{

	int i, j, k;

	if(wr_dim == 2) {
		_Pragma("loopbound min ARRAY_RD_FACTOR max ARRAY_RD_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ROWS max ROWS")
			for(j = 0; j < m; j++) {
				_Pragma("loopbound min ARRAY_RD_DIV max ARRAY_RD_DIV")				
				for(k = 0; k < n/factor; k++) {
					array[j][k + i * n / factor] 
						= *(bank_ptr_array[i + array_bank0] + k + m * j / factor);
				}
			}
		}
	}

	else if(wr_dim == 1) {
		_Pragma("loopbound min ARRAY_RD_FACTOR max ARRAY_RD_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ARRAY_RD_DIV max ARRAY_RD_DIV")			
			for(j = 0; j < m/factor; j++) {
				_Pragma("loopbound min COLS max COLS")
				for(k = 0; k < n; k++) {
					array[j + i * m / factor][k] 
						= *(bank_ptr_array[i + array_bank0] + k + n * j);
				}
			}
		}
	}
}

void read_array_spm(volatile _SPM mat_type(*array)[ROWS][COLS], int n,
					int m, int factor, int array_bank0,
					volatile _IODEV mat_type** bank_ptr_array, int wr_dim)
{

	int i, j, k;

	if(wr_dim == 2) {
		_Pragma("loopbound min ARRAY_RD_FACTOR max ARRAY_RD_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ROWS max ROWS")
			for(j = 0; j < m; j++) {
				_Pragma("loopbound min ARRAY_RD_DIV max ARRAY_RD_DIV")				
				for(k = 0; k < n/factor; k++) {
					(*array)[j][k + i * n / factor] = *(bank_ptr_array[i + array_bank0] + k + m * j / factor);
				}
			}
		}
	}

	else if(wr_dim == 1) {
		_Pragma("loopbound min ARRAY_RD_FACTOR max ARRAY_RD_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ARRAY_RD_DIV max ARRAY_RD_DIV")			
			for(j = 0; j < m/factor; j++) {
				_Pragma("loopbound min COLS max COLS")
				for(k = 0; k < n; k++) {
					(*array)[j + i * m / factor][k] = *(bank_ptr_array[i + array_bank0] + k + n*j) ;
				}
			}
		}
	}
}

void read_array_uncached(volatile _UNCACHED mat_type(*array)[ROWS][COLS],
						 int n, int m, int factor, int array_bank0,
						 volatile _IODEV mat_type** bank_ptr_array, int wr_dim)
{

	int i, j, k;

	if(wr_dim == 2) {
		_Pragma("loopbound min ARRAY_RD_FACTOR max ARRAY_RD_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ROWS max ROWS")			
			for(j = 0; j < m; j++) {
				_Pragma("loopbound min ARRAY_RD_DIV max ARRAY_RD_DIV")				
				for(k = 0; k < n/factor; k++) {
					(*array)[j][k + i * n / factor] = *(bank_ptr_array[i+array_bank0] + k + m * j / factor);
				}
			}
		}
	}

	else if(wr_dim == 1) {
		_Pragma("loopbound min ARRAY_RD_FACTOR max ARRAY_RD_FACTOR")		
		for(i = 0; i < factor; i++) {
			_Pragma("loopbound min ARRAY_RD_DIV max ARRAY_RD_DIV")			
			for(j = 0; j < m/factor; j++) {
				_Pragma("loopbound min COLS max COLS")				
				for(k = 0; k < n; k++) {
					(*array)[j + i * m / factor][k] = *(bank_ptr_array[i + array_bank0] + k + n * j);
				}
			}
		}
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

void write_vector_spm(volatile _SPM mat_type(*vec)[], int length, int factor,
					  int vec_bank0, volatile _IODEV mat_type** bank_ptr_array)
{

	int i, j;

	_Pragma("loopbound min VEC_WR_FACTOR max VEC_WR_FACTOR")
	for(i = 0; i < factor; i++) {
		_Pragma("loopbound min VEC_WR_DIV max VEC_WR_DIV")		
		for(j = 0; j < length/factor; j++) {

			*(bank_ptr_array[i + vec_bank0] + j) = (*vec)[j + i * length / factor];
		}
	}
}

void write_vector_uncached(volatile _UNCACHED mat_type(*vec)[], int length,
						   int factor, int vec_bank0,
						   volatile _IODEV mat_type** bank_ptr_array)
{

	int i, j;

	_Pragma("loopbound min VEC_WR_FACTOR max VEC_WR_FACTOR")
	for(i = 0; i < factor; i++) {
		_Pragma("loopbound min VEC_WR_DIV max VEC_WR_DIV")		
		for(j = 0; j < length/factor; j++) {

			*(bank_ptr_array[i + vec_bank0] + j) = (*vec)[j + i * length / factor];
		}
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

void read_vector_spm(volatile _SPM mat_type(*vec)[], int length,
					 int factor, int vec_bank0,
					 volatile _IODEV mat_type** bank_ptr_array)
{

	int i, j;

	_Pragma("loopbound min VEC_RD_FACTOR max VEC_RD_FACTOR")
	for(i = 0; i < factor; i++) {
		_Pragma("loopbound min VEC_RD_DIV max VEC_RD_DIV")						
		for(j = 0; j < length/factor; j++) {

			(*vec)[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}
}

void read_vector_uncached(volatile _UNCACHED  mat_type(*vec)[], int length,
						  int factor, int vec_bank0,
						  volatile _IODEV mat_type** bank_ptr_array)
{

	int i, j;

	_Pragma("loopbound min VEC_RD_FACTOR max VEC_RD_FACTOR")
	for(i = 0; i < factor; i++) {
		_Pragma("loopbound min VEC_RD_DIV max VEC_RD_DIV")								
		for(j = 0; j < length/factor; j++) {

			(*vec)[j + i * length / factor] = *(bank_ptr_array[i + vec_bank0] + j);
		}
	}
}