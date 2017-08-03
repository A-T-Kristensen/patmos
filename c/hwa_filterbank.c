
#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"


#define BRAM_BASE_READ 		0xF00B1000

void filterbank_init(void);
int filterbank_main(mat_type r[256],
					mat_type H[8][32],
					mat_type F[8][32],
					mat_type y[256]);

int filterbank_return(void);

int filterbank_main_wcet(mat_type r[256],
						 mat_type H[8][32],
						 mat_type F[8][32],
						 mat_type y[256]) __attribute__((noinline));

void filter_init(mat_type r[256],
				 mat_type H[8][32],
				 mat_type F[8][32],
				 mat_type y[256]);

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

void filter_init(mat_type r[256], mat_type H[8][32],
				 mat_type F[8][32], mat_type y[256])
{

	int i, j;

	for(i = 0; i < 256; i++) {
		r[i] = i + 1;
		y[i] = 0;
	}

	for(i = 0; i < 32; i++) {
		for(j = 0; j < 8; j++) {
			H[j][i] = i * 32 + j * 8 + j + i + j + 1;
			F[j][i] = i * j + j * j + j + i;
		}
	}
}


int _Pragma("entrypoint") filterbank_main_wcet(mat_type r[256],
		mat_type H[8][32],
		mat_type F[8][32],
		mat_type y[256])
{


	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);
	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	write_vector(r, 256, 0, 0);
	write_vector(y, 256, 0, 1);
	write_array(H, 32, 8, 0, 2, 1);
	write_array(F, 32, 8, 0, 3, 1);

	*hls_ptr = 1;
	*hls_ptr;

	read_vector(y, 256, 0, BRAM_BASE_READ);

	return 0;
}

int filterbank_main(mat_type r[256], mat_type H[8][32],
					mat_type F[8][32], mat_type y[256])
{
	int err_cnt = 0;

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr = (volatile _IODEV int *) HWA_CTRL_BASE;

	int i, j;

	unsigned long long start_compute, stop_compute, return_compute = 0;
	unsigned long long start_transfer, stop_transfer, return_transfer = 0;

	printf("Benchmarking \n");

	// Move data into hardware

	start_transfer = get_cpu_cycles();

	write_vector(r, 256, 0, 0);
	//write_vector(y, 256, 0, 1);
	write_array(H, 32, 8, 0, 2, 1);
	write_array(F, 32, 8, 0, 3, 1);

	stop_transfer = get_cpu_cycles();
	return_transfer = stop_transfer-start_transfer-CYCLE_CALIBRATION;

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

	start_transfer = get_cpu_cycles();

	read_vector(y, 256, 0, BRAM_BASE_READ);

	stop_transfer = get_cpu_cycles();
	return_transfer += stop_transfer-start_transfer-CYCLE_CALIBRATION;

	if(!((int)(y[0]) - 9408)) {
		puts("Results correct");
	} else {
		puts("Results incorrect");
	}

	print_benchmark(return_compute, return_transfer);

	return (int)((y[0]) - 9408);
}

/*
  Main function
*/

int main(void)
{

	mat_type r[256];
	mat_type y[256];
	mat_type H[8][32];
	mat_type F[8][32];

	filterbank_init();
	filter_init(r, H, F, y);

#if(WCET)

	return filterbank_main_wcet(r, H, F, y);

#else

	return filterbank_main(r, H, F, y);

#endif
}