/*

  This program is part of the TACLeBench benchmark suite.
  Version V 2.0

  Name: fir2dim

  Author: Juan Martinez Velarde

  Function: prime calculates whether numbers are prime.

  Source: DSP-Stone
		  http://www.ice.rwth-aachen.de/research/tools-projects/entry/detail/dspstone/

  Original name: fir2dim_float

  Changes: no major functional changes

  License: may be used, modified, and re-distributed freely

*/

/*
	To run this on hwa, in benchmark.h, set NBANKS to 2.
 */

#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

#define IMAGEDIM      4
#define ARRAYDIM      (IMAGEDIM + 2)
#define COEFFICIENTS  3

#define COEFF_OFFSET 0
#define IMAGE_OFFSET (COEFFICIENTS*COEFFICIENTS)
#define ARRAY_OFFSET (IMAGE_OFFSET+IMAGEDIM*IMAGEDIM)
#define SIZE (COEFFICIENTS * COEFFICIENTS + 1*IMAGEDIM * IMAGEDIM + ARRAYDIM * ARRAYDIM)

struct filter_data {
	mat_type fir2dim_input[SIZE];
	mat_type fir2dim_output_hw[IMAGEDIM * IMAGEDIM];
};

volatile _SPM struct filter_data *spm_filter = (volatile _SPM struct filter_data *) SPM_BASE;

/*
  Forward declaration of functions
*/

void fir2dim_initSeed(void);

long fir2dim_randomInteger();

void fir2dim_pin_down(mat_type *pimage, mat_type *parray,
					  mat_type *pcoeff, mat_type *poutput);

void fir2dim_init(mat_type fir2dim_coefficients[COEFFICIENTS * COEFFICIENTS],
				  mat_type fir2dim_image[IMAGEDIM * IMAGEDIM],
				  mat_type fir2dim_array[ARRAYDIM * ARRAYDIM],
				  mat_type fir2dim_output[IMAGEDIM * IMAGEDIM]);

int fir2dim_return(int fir2dim_result);

int main(void);
int fir2dim_main_wcet(void) __attribute__((noinline));

int fir2dim_result_hw;
mat_type fir2dim_input[SIZE];
mat_type fir2dim_coefficients[COEFFICIENTS * COEFFICIENTS];
mat_type fir2dim_image[IMAGEDIM * IMAGEDIM];
mat_type fir2dim_array[ARRAYDIM * ARRAYDIM];
mat_type fir2dim_output_hw[IMAGEDIM * IMAGEDIM];

/*
  Initialization- and return-value-related functions
*/

void fir2dim_init(mat_type fir2dim_coefficients[COEFFICIENTS * COEFFICIENTS],
				  mat_type fir2dim_image[IMAGEDIM * IMAGEDIM],
				  mat_type fir2dim_array[ARRAYDIM * ARRAYDIM],
				  mat_type fir2dim_output[IMAGEDIM * IMAGEDIM])
{

	unsigned int i;
	unsigned char *p;
	volatile char bitmask = 0;

	/*
	Apply volatile XOR-bitmask to entire input array.
	*/
	p = (unsigned char *) &fir2dim_coefficients[ 0 ];
	_Pragma("loopbound min 36 max 36")
	for(i = 0; i < sizeof(fir2dim_coefficients); ++i, ++p) {
		*p ^= bitmask;
	}

	p = (unsigned char *) &fir2dim_image[ 0 ];
	_Pragma("loopbound min 64 max 64")
	for(i = 0; i < sizeof(fir2dim_image); ++i, ++p) {
		*p ^= bitmask;
	}

	p = (unsigned char *) &fir2dim_array[ 0 ];
	_Pragma("loopbound min 144 max 144")
	for(i = 0; i < sizeof(fir2dim_array); ++i, ++p) {
		*p ^= bitmask;
	}
	p = (unsigned char *) &fir2dim_output[ 0 ];
	_Pragma("loopbound min 64 max 64")
	for(i = 0; i < sizeof(fir2dim_output); ++i, ++p) {
		*p ^= bitmask;
	}
}

int fir2dim_return(int fir2dim_result)
{
	return (fir2dim_result - 14 != 0);
}

/*
  Helper functions
*/

void fir2dim_pin_down(mat_type *pimage, mat_type *parray,
					  mat_type *pcoeff, mat_type *poutput)
{

	mat_type i, f;

	_Pragma("loopbound min 4 max 4")
	for(i = 0 ; i < IMAGEDIM ; i++) {
		_Pragma("loopbound min 4 max 4")

		for(f = 0 ; f < IMAGEDIM ; f++) {
			*pimage++ = 1 ;
		}
	}

	pimage = pimage - IMAGEDIM * IMAGEDIM;

	_Pragma("loopbound min 9 max 9")
	for(i = 0; i < COEFFICIENTS * COEFFICIENTS; i++) {
		*pcoeff++ = 1;
	}

	_Pragma("loopbound min 6 max 6")
	for(i = 0 ; i < ARRAYDIM ; i++) {
		*parray++ = 0 ;
	}

	_Pragma("loopbound min 4 max 4")
	for(f = 0 ; f < IMAGEDIM; f++) {
		*parray++ = 0 ;

		_Pragma("loopbound min 4 max 4")
		for(i = 0 ; i < IMAGEDIM ; i++) {
			*parray++ = *pimage++;
		}

		*parray++ = 0 ;
	}

	_Pragma("loopbound min 6 max 6")
	for(i = 0 ; i < ARRAYDIM ; i++) {
		*parray++ = 0 ;
	}

	_Pragma("loopbound min 16 max 16")
	for(i = 0 ; i < IMAGEDIM * IMAGEDIM; i++) {
		*poutput++ = 0 ;
	}
}

int _Pragma("entrypoint") fir2dim_main_wcet(void)
{

	int i;

	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;

	write_vector_spm(spm_filter->fir2dim_input, SIZE, 1, 0);

	*hls_ptr = 1;
	*hls_ptr;

	read_vector_spm(spm_filter->fir2dim_output_hw, IMAGEDIM * IMAGEDIM, 1, 0xF00B1000);

	return 0;
}


int main(void)
{

	int i;

	// Initialize

	fir2dim_init(fir2dim_coefficients, fir2dim_image,
				 fir2dim_array, fir2dim_output_hw);

	fir2dim_pin_down(&fir2dim_image[0], &fir2dim_array[0],
					 &fir2dim_coefficients[0], &fir2dim_output_hw[0]);

	for(i = 0; i < COEFFICIENTS*COEFFICIENTS; i++) {
		spm_filter->fir2dim_input[COEFF_OFFSET + i] = fir2dim_coefficients[i];
	}

	for(i = 0; i < IMAGEDIM*IMAGEDIM; i++) {
		spm_filter->fir2dim_input[IMAGE_OFFSET + i] = fir2dim_image[i];
	}

	for(i = 0; i < ARRAYDIM*ARRAYDIM; i++) {
		spm_filter->fir2dim_input[ARRAY_OFFSET + i] = fir2dim_array[i];
	}

#if(WCET)

	return fir2dim_main_wcet();

#else

	return 0;

#endif
}
