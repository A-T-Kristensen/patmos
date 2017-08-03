/*
	This is a minimal C program executed on the FPGA version of Patmos.
	An embedded test of a vivado HLS HwA module: Matrix multiplication on
	an array of dimension DIM partitionen into NBANKS memory banks.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: BSD License
 */

#include "libhwa/hwa_lib.h"
#include "libhwa/hwa_bram.h"
#include "libhwa/hwa_test.h"

#define SAMPLE_RATE 11025

#define MAX_SIZE 100

#define PI 3141

#define TEST_SIZE 3

#define IN_END TEST_SIZE+1

void init(int test_data[TEST_SIZE]);
int adpcm_sin(int rad);
int adpcm_cos(int rad);
int adpcm_abs(int n);

int enc_return(int compressed[TEST_SIZE]);
int dec_return(int dec_result[TEST_SIZE]);
int adpcm_main(void);
int adpcm_main_wcet() __attribute__((noinline));

/* Input data for the decoder usually generated by the encoder. */
int compressed[TEST_SIZE] = {0};
/* Output data frome the decoder */
int dec_result[TEST_SIZE] = {0};

/* Input data for the encoder usually generated by the init function. */
int test_data[TEST_SIZE];


int adpcm_abs(int n)
{
	int m;

	if(n >= 0)
		m = n;
	else
		m = -n;
	return m;
}

int adpcm_sin(int rad)
{
	int diff;
	int app = 0;
	int inc = 1;

	/* MAX dependent on rad's value, say 50 */
	while(rad > 2 * PI) {
		rad -= 2 * PI;
	}

	/* MAX dependent on rad's value, say 50 */
	while(rad < -2 * PI) {
		rad += 2 * PI;
	}

	diff = rad;
	app = diff;
	diff = (diff * (-(rad*rad))) / ((2 * inc) * (2 * inc + 1));
	app = app + diff;
	inc++;

	/* REALLY: while(my_fadpcm_abs(diff) >= 0.00001) { */
	/* MAX: 1000 */
	while(adpcm_abs(diff) >= 1) {
		diff = (diff * (-(rad*rad))) / ((2 * inc) * (2 * inc + 1));
		app = app + diff;
		inc++;
	}

	return app;
}

int adpcm_cos(int rad)
{
	return(adpcm_sin(PI / 2 - rad));
}

void init(int test_data[TEST_SIZE])
{
	int i, j, f;
	int x = 0;

	/* read in amplitude and frequency for test data */
	//j = 100;
	j=10;
	f = 20000;

	/* 16 KHz sample rate */
	/* XXmain_0, MAX: 2 */
	/* Since the number of times we loop in my_sin depends on the argument we
	   add the fact: xxmain_0:[]: */
	for(i = 0 ; i < TEST_SIZE ; i++) {
		test_data[i] = (int) j * adpcm_cos(f * PI * i);
		//test_data[i] = (int) j*sin(2*f*i*3.14159265);

		test_data[i] += x;
	}
}

int enc_return(int compressed[TEST_SIZE])
{
	int i;
	int check_sum = 0;


	for(i = 0 ; i < TEST_SIZE ; i += 2) {
		check_sum += compressed[i/2];
	}

	return check_sum != 385;
}

int dec_return(int dec_result[TEST_SIZE])
{
	int i;
	int check_sum = 0;

	for(i = 0; i < TEST_SIZE; i++) {
		check_sum += (dec_result[i]);
	}

	return check_sum != -2;
}

int _Pragma("entrypoint") adpcm_main_wcet()
{
	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	write_vector(test_data, TEST_SIZE, 0, 0);

	*(hls_ptr + 1) = 0; // Select encoder
	*(hls_ptr + 2) = TEST_SIZE;	// Set the size

	*hls_ptr = 1;

	read_vector(compressed, TEST_SIZE, 0, 0xF00B1000);

	return 0;
}

int adpcm_main()
{

	volatile _IODEV int *hls_ptr  = (volatile _IODEV int *) HWA_CTRL_BASE;

	unsigned long long start_compute, stop_compute, return_compute = 0;
	unsigned long long start_transfer, stop_transfer, return_transfer = 0;

	int err_cnt = 0;

	start_transfer = get_cpu_cycles();

	write_vector(test_data, TEST_SIZE, 0, 0);

	*(hls_ptr + 1) = 0; // Select encoder
	*(hls_ptr + 2) = TEST_SIZE;	// Set the size

	stop_transfer = get_cpu_cycles();
	return_transfer = stop_transfer-start_transfer-CYCLE_CALIBRATION;

	start_compute = get_cpu_cycles();

	*hls_ptr = 1;

	while((*hls_ptr) != 1);

	stop_compute = get_cpu_cycles();
	return_compute = stop_compute-start_compute-CYCLE_CALIBRATION;

	start_transfer = get_cpu_cycles();

	read_vector(compressed, TEST_SIZE, 0, 0xF00B1000);

	stop_transfer = get_cpu_cycles();
	return_transfer += stop_transfer-start_transfer-CYCLE_CALIBRATION;

	if(!enc_return(compressed)) {
		puts("Results correct");
	} else {
		puts("Results incorrect");
	}

	print_benchmark(return_compute, return_transfer);

	return enc_return(compressed);
}

int main()
{

	init(test_data);

#if(WCET)

	return adpcm_main_wcet();

#else

	printf("Benchmarking \n");

	return adpcm_main();

#endif
}
