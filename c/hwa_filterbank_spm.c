
#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

#define BRAM_BASE_READ 		0xF00B1000


struct filter_data {
	mat_type r[256];
	mat_type y[256];
	mat_type H[8][32];
	mat_type F[8][32];
};

volatile _SPM struct filter_data *spm_filter = (volatile _SPM struct filter_data *) SPM_BASE;
volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

void filterbank_init(void);
int filterbank_main(void) __attribute__ ((noinline));
int filterbank_main_wcet(void) __attribute__((noinline));
int filterbank_return(void);

/*
  Declaration of global variables
*/

static int filterbank_return_value;
static int filterbank_numiters;

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

	for(i = 0; i < 256; i++) {
		spm_filter->r[i] = i + 1;
		spm_filter->y[i] = 0;
	}

	for(i = 0; i < 32; i++) {
		for(j = 0; j < 8; j++) {
			spm_filter->H[j][i] = i * 32 + j * 8 + j + i + j + 1;
			spm_filter->F[j][i] = i * j + j * j + j + i;
		}
	}

}

int _Pragma("entrypoint") filterbank_main_wcet(void)
{

#if(WRITE)

	write_vector_spm(spm_filter->r, 256, 0, 0);
	write_array_spm(spm_filter->H, 32, 8, 0, 2, 1);
	write_array_spm(spm_filter->F, 32, 8, 0, 3, 1);

#endif

#if(COMP)

	_Pragma("loopbound min 2 max 2")
	while(filterbank_numiters-- > 0) {

		*hls_ptr = 1;
		*hls_ptr = 0;

		_Pragma("loopbound min 1 max 1")
		while((*hls_ptr) != 1){
		}	
	}

#endif		

#if(READ)

	read_vector_spm(spm_filter->y, 256, 0, BRAM_BASE_READ);

#endif		

	return 0;
}

unsigned long long start_compute, stop_compute, return_compute = 0;
unsigned long long start_write, stop_write, return_write = 0;
unsigned long long start_read, stop_read, return_read = 0;	

int __attribute__ ((noinline)) filterbank_main(void)
{
	// Move data into hardware

#if(WRITE)

	start_write = get_cpu_cycles();

	write_vector_spm(spm_filter->r, 256, 0, 0);
	write_array_spm(spm_filter->H, 32, 8, 0, 2, 1);
	write_array_spm(spm_filter->F, 32, 8, 0, 3, 1);

	stop_write = get_cpu_cycles();
	return_write = stop_write-start_write-CYCLE_CALIBRATION;

#endif

#if(COMP)

	start_compute = get_cpu_cycles();

	while(filterbank_numiters-- > 0) {

		// Start HLS module

		*hls_ptr = 1;
		*hls_ptr = 0;

		// Poll status of HLS module

		while((*hls_ptr) != 1);

	}

	stop_compute = get_cpu_cycles();
	return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;

#endif

#if(READ)

	start_read = get_cpu_cycles();

	read_vector_spm(spm_filter->y, 256, 0, BRAM_BASE_READ);

	stop_read = get_cpu_cycles();
	return_read = stop_read-start_read-CYCLE_CALIBRATION;

#endif

	return 0;
}

/*
  Main function
*/

int main(void)
{

	filter_init();
	filterbank_init();

#if(WCET)

	return filterbank_main_wcet();

#else

	filterbank_main();

	if(!(int)((spm_filter->y[0]) - 9408)) {
		puts("Results correct");
	} else {
		puts("Results incorrect");
	}

	print_benchmark(return_compute, return_write, return_read);

	return (int)((spm_filter->y[0]) - 9408);	

#endif

}