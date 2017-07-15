
#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

struct filter_data {
	mat_type r[256];
	mat_type y[256];
	mat_type H[8][32];
	mat_type F[8][32];
};

volatile _SPM struct filter_data *spm_filter = (volatile _SPM struct filter_data *) SPM_BASE;

void filterbank_init(void);
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
	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	write_vector_spm(spm_filter->r, 256, 1, 0);
	write_vector_spm(spm_filter->y, 256, 1, 1);
	write_array_spm(spm_filter->H, 32, 8, 1, 2, 1);
	write_array_spm(spm_filter->F, 32, 8, 1, 3, 1);

	*hls_ptr = 1;
	*hls_ptr;

	read_vector_spm(spm_filter->y, 256, 1, 0xF00B1000);

	return (int)(spm_filter->y[0]) - 9408;
}

int main(void)
{

	filter_init();
	filterbank_init();

#if(WCET)

	return filterbank_main_wcet();

#else

	return 0;

#endif

}