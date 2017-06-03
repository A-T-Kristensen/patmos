
#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

struct filter_data {
	mat_type r[256];
	mat_type y[256];
	mat_type H[8][32];
	mat_type F[8][32];
};

volatile _UNCACHED struct filter_data *test_filter;

void filterbank_init(void);
int filterbank_main(void);
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
		test_filter->r[i] = i + 1;
		test_filter->y[i] = 0;
	}

	for(i = 0; i < 32; i++) {
		for(j = 0; j < 8; j++) {
			test_filter->H[j][i] = i * 32 + j * 8 + j + i + j + 1;
			test_filter->F[j][i] = i * j + j * j + j + i;
		}
	}

}

int _Pragma("entrypoint") filterbank_main_wcet(void)
{

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);
	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;


	write_vector_uncached(&test_filter->r, 256, 1, 0, bank_ptr_array);
	write_vector_uncached(&test_filter->y, 256, 1, 1, bank_ptr_array);
	write_array_uncached(&test_filter->H, 32, 8, 1, 2, bank_ptr_array, 1);
	write_array_uncached(&test_filter->F, 32, 8, 1, 3, bank_ptr_array, 1);

	*hls_ptr = 1;
	*hls_ptr;	

	read_vector_uncached(&test_filter->y, 256, 1, 1, bank_ptr_array);

	return (int)(test_filter->y[0]) - 9408;
}

int filterbank_main(void)
{

	volatile _IODEV mat_type *bank_ptr_array[NBANKS];
	bank_ptrs(bank_ptr_array, NBANKS);

	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	int i, j;

	unsigned long long start_compute, stop_compute, return_compute = 0;
	unsigned long long start_transfer, stop_transfer, return_transfer = 0;

	printf("Benchmarking \n");

	// Move data into hardware

	start_transfer = get_cpu_cycles();

	write_vector_uncached(&test_filter->r, 256, 1, 0, bank_ptr_array);
	write_vector_uncached(&test_filter->y, 256, 1, 1, bank_ptr_array);
	write_array_uncached(&test_filter->H, 32, 8, 1, 2, bank_ptr_array, 1);
	write_array_uncached(&test_filter->F, 32, 8, 1, 3, bank_ptr_array, 1);

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

	read_vector_uncached(&test_filter->y, 256, 1, 1, bank_ptr_array);

	stop_transfer = get_cpu_cycles();
	return_transfer += stop_transfer-start_transfer-CYCLE_CALIBRATION;

	print_benchmark(return_compute, return_transfer);

	return (int)(test_filter->y[0]) - 9408;
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

	return filterbank_main();

#endif

}