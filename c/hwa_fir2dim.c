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

#define BRAM_BASE_READ 		0xF00B1000

#define IMAGEDIM      4
#define ARRAYDIM      (IMAGEDIM + 2)
#define COEFFICIENTS  3

#define COEFF_OFFSET 0
#define IMAGE_OFFSET (COEFFICIENTS*COEFFICIENTS)
#define ARRAY_OFFSET (IMAGE_OFFSET+IMAGEDIM*IMAGEDIM)
#define TEST_SIZE (COEFFICIENTS * COEFFICIENTS + 1*IMAGEDIM * IMAGEDIM + ARRAYDIM * ARRAYDIM)

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
int fir2dim_main(void);
int fir2dim_main_wcet(void) __attribute__((noinline));

int fir2dim_result_hw;
mat_type fir2dim_input[TEST_SIZE];
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

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);
	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;

	write_vector(fir2dim_input, TEST_SIZE, 0, 0);

	*hls_ptr = 1;
	*hls_ptr;

	read_vector(fir2dim_output_hw, IMAGEDIM * IMAGEDIM, 0, BRAM_BASE_READ);

	return 0;
}

unsigned long long start_compute, stop_compute, return_compute = 0;
unsigned long long start_write, stop_write, return_write = 0;
unsigned long long start_read, stop_read, return_read = 0;	

int fir2dim_main(void)
{

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	// Run hardware

	start_write = get_cpu_cycles();

	write_vector(fir2dim_input, TEST_SIZE, 0, 0);

	stop_write = get_cpu_cycles();
	return_write = stop_write-start_write-CYCLE_CALIBRATION;

	// Start HLS module

	start_compute = get_cpu_cycles();

	*hls_ptr = 1;

	// Poll status of HLS module

	while((*hls_ptr) != 1);

	stop_compute = get_cpu_cycles();
	return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;

	start_read = get_cpu_cycles();

	read_vector(fir2dim_output_hw, IMAGEDIM * IMAGEDIM, 0, BRAM_BASE_READ);

	stop_read = get_cpu_cycles();
	return_read = stop_read-start_read-CYCLE_CALIBRATION;
	
	// Check results

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

	// Assign values to input array

	// Assign the values
	for(i = 0; i < COEFFICIENTS*COEFFICIENTS; i++) {
		fir2dim_input[COEFF_OFFSET + i] = fir2dim_coefficients[i];
	}

	for(i = 0; i < IMAGEDIM*IMAGEDIM; i++) {
		fir2dim_input[IMAGE_OFFSET + i] = fir2dim_image[i];
	}

	for(i = 0; i < ARRAYDIM*ARRAYDIM; i++) {
		fir2dim_input[ARRAY_OFFSET + i] = fir2dim_array[i];
	}


#if(WCET)

	return fir2dim_main_wcet();

#else

	fir2dim_main();

	print_benchmark(return_compute, return_write, return_read);	

	fir2dim_result_hw = fir2dim_output_hw[0] + fir2dim_output_hw[5] + fir2dim_array[9];

	if(!fir2dim_return(fir2dim_result_hw)) {
		puts("Results correct");
	} else {
		puts("Results incorrect");
	}	

	return fir2dim_return(fir2dim_result_hw);	

#endif

}