/*

  This program is part of the TACLeBench benchmark suite.
  Version 2.0

  Name: filterbank

  Author: unknown

  Function: Creates a filter bank to perform multirate signal processing.
            The coefficients for the sets of filters are created in the
            top-level init function, and passed down through the init
            functions to FIR filter objects.
            On each branch, a delay, filter, and downsample is performed,
            followed by an upsample, delay, and filter.

  Source: StreamIt
          (http://groups.csail.mit.edu/cag/streamit/shtml/benchmarks.shtml)

  Original name: filterbank

  Changes: See ChangeLog.txt

  License: MIT License

*/

#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_test.h"

/*
  Forward declaration of functions
*/



void filterbank_init(void);
void filterbank_main(void) __attribute__((noinline));
int filterbank_return(void);
void filter_init();
void filterbank_core(volatile _SPM mat_type(*r)[256],
					 volatile _SPM mat_type(*y)[256],
					 volatile _SPM mat_type(*H)[8][32],
					 volatile _SPM mat_type(*F)[8][32]);


/*
  Declaration of global variables
*/

static int filterbank_return_value;
static int filterbank_numiters;


struct filter_data {
	mat_type r[ 256 ];
	mat_type y[ 256 ];
	mat_type H[ 8 ][ 32 ];
	mat_type F[ 8 ][ 32 ];
};

volatile _SPM struct filter_data *spm_filter = (volatile _SPM struct filter_data *) SPM_BASE;

const unsigned int ADDR_H	= 1024*sizeof(int);
const unsigned int ADDR_DN 	= ADDR_H + 256*sizeof(int);
const unsigned int ADDR_UP	= ADDR_DN + 32*sizeof(int);
const unsigned int ADDR_F 	= ADDR_UP + 256*sizeof(int);

//mat_type Vect_H[ 256 ]; /* (output of the H) */
//mat_type Vect_Dn[(int) 256 / 8 ];    /* output of the down sampler; */
//mat_type Vect_Up[ 256 ]; /* output of the up sampler; */
//mat_type Vect_F[ 256 ]; /* this is the output of the */

volatile _SPM int *Vect_H_p 	= (volatile _SPM int *) ADDR_H;
volatile _SPM int *Vect_Dn_p 	= (volatile _SPM int *) ADDR_DN;
volatile _SPM int *Vect_Up_p 	= (volatile _SPM int *) ADDR_UP;
volatile _SPM int *Vect_F_p 	= (volatile _SPM int *) ADDR_F;

/*
  Initialization- and return-value-related functions
*/

void filterbank_init(void)
{
	filterbank_numiters = 2;
}


int filterbank_return(void)
{
	return filterbank_return_value;
}

void filter_init()
{

	int i, j;

	_Pragma("loopbound min 256 max 256")
	for(i = 0; i < 256; i++) {
		spm_filter->r[i] = i + 1;
	}

	_Pragma("loopbound min 32 max 32")
	for(i = 0; i < 32; i++) {

		_Pragma("loopbound min 8 max 8")
		for(j = 0; j < 8; j++) {
			spm_filter->H[j][i] = i * 32 + j * 8 + j + i + j + 1;
			spm_filter->F[j][i] = i * j + j * j + j + i;
		}
	}
}


/*
  Core benchmark functions
*/

void _Pragma("entrypoint") filterbank_main(void)
{

	_Pragma("loopbound min 2 max 2")
	while(filterbank_numiters-- > 0)
		filterbank_core(&spm_filter->r, &spm_filter->y, &spm_filter->H, &spm_filter->F);

	filterbank_return_value = (int)(spm_filter->y[0]) - 9408;
}


/* the FB core gets the input vector (r) , the filter responses H and F and */
/* generates the output vector(y) */
void filterbank_core(volatile _SPM mat_type(*r)[256],
					 volatile _SPM mat_type(*y)[256],
					 volatile _SPM mat_type(*H)[8][32],
					 volatile _SPM mat_type(*F)[8][32])
{
	int i, j, k;

	_Pragma("loopbound min 256 max 256")
	for(i = 0; i < 256; i++)
		(*y)[ i ] = 0;

	_Pragma("loopbound min 8 max 8")
	for(i = 0; i < 8; i++) {

		/* convolving H */
		_Pragma("loopbound min 256 max 256")
		for(j = 0; j < 256; j++) {
			Vect_H_p[ j ] = 0;
			_Pragma("loopbound min 1 max 32")
			for(k = 0; ((k < 32) & ((j - k) >= 0)); k++)
				Vect_H_p[ j ] += (*H)[ i ][ k ] * (*r)[ j - k ];
		}

		/* Down Sampling */
		_Pragma("loopbound min 32 max 32")
		for(j = 0; j < 256 / 8; j++)
			Vect_Dn_p[ j ] = Vect_H_p[ j * 8 ];

		/* Up Sampling */
		_Pragma("loopbound min 256 max 256")
		for(j = 0; j < 256; j++)
			Vect_Up_p[ j ] = 0;
		_Pragma("loopbound min 32 max 32")
		for(j = 0; j < 256 / 8; j++)
			Vect_Up_p[ j * 8 ] = Vect_Dn_p[ j ];

		/* convolving F */
		_Pragma("loopbound min 256 max 256")
		for(j = 0; j < 256; j++) {
			Vect_F_p[ j ] = 0;
			_Pragma("loopbound min 1 max 32")
			for(k = 0; ((k < 32) & ((j - k) >= 0)); k++)
				Vect_F_p[ j ] += (*F)[ i ][ k ] * Vect_Up_p[ j - k ];
		}

		/* adding the results to the y matrix */

		_Pragma("loopbound min 256 max 256")
		for(j = 0; j < 256; j++)
			(*y)[ j ] += Vect_F_p[ j ];
	}
}

/*
  Main function
*/

int main(void)
{

	filter_init();
	filterbank_init();

#if(WCET)

	filterbank_main();

#else

	unsigned long long start_cycle, stop_cycle, return_cycles = 0;

	printf("Benchmarking \n");

	start_cycle = get_cpu_cycles();

	filterbank_main();

	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-CYCLE_CALIBRATION;

	print_benchmark(return_cycles, 0, 0);

#endif

	return filterbank_return();
}