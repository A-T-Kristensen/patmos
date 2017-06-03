/*

	This program is part of the TACLeBench benchmark suite.
	Version V 1.x

	Name: minver

	Author: Sung-Soo Lim

	Function: Matrix inversion for DIMxDIM floating point matrix.

	Source: SNU-RT Benchmark Suite, via MRTC
		   http://www.mrtc.mdh.se/projects/wcet/wcet_bench/minver/minver.c

	Changes: a brief summary of major functional changes (not formatting)

	License: may be used, modified, and re-distributed freely, but
			 the SNU-RT Benchmark Suite must be acknowledged

*/

/*
	This program is derived from the SNU-RT Benchmark Suite for Worst
	Case Timing Analysis by Sung-Soo Lim

	Original source: Turbo C Programming for Engineering by Hyun Soo Ahn
*/

/*
	Forward declaration of functions
*/

#include "libhwa/hwa_lib.h"
#include "libminver/minver_init.h"
#include "libhwa/hwa_test.h"

int minver_minver(float minver_a[DIM][DIM],
				  int side, float eps)  __attribute__((noinline));

float minver_fabs(float n);
int main(void);


float minver_fabs(float n)
{
	float f;

	if(n >= 0)
		f = n;
	else
		f = -n;
	return f;
}

int _Pragma("entrypoint") minver_minver(float minver_a[DIM][DIM],
										int side, float eps)
{

	int work[ 500 ], i, j, k, iw;
	int r = 0;
	float w, wmax, pivot, api, w1;
	float minver_det;

	if(side < 2 || side > 500 || eps <= 0.0)
		return (999);
	w1 = 1.0;
	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < side; i++)
		work[ i ] = i;
	_Pragma("loopbound min DIM max DIM")
	for(k = 0; k < side; k++) {
		wmax = 0.0;
		_Pragma("loopbound min 1 max DIM")
		for(i = k; i < side; i++) {
			w = minver_fabs(minver_a[ i ][ k ]);
			if(w > wmax) {
				wmax = w;
				r = i;
			}
		}
		pivot = minver_a[ r ][ k ];
		api = minver_fabs(pivot);
		if(api <= eps) {
			minver_det = w1;
			return (1);
		}
		w1 *= pivot;
		if(r != k) {
			w1 = -w;
			iw = work[ k ];
			work[ k ] = work[ r ];
			work[ r ] = iw;
			_Pragma("loopbound min DIM max DIM")
			for(j = 0; j < side; j++) {
				w = minver_a[ k ][ j ];
				minver_a[ k ][ j ] = minver_a[ r ][ j ];
				minver_a[ r ][ j ] = w;
			}
		}
		_Pragma("loopbound min DIM max DIM")
		for(i = 0; i < side; i++)
			minver_a[ k ][ i ] /= pivot;
		_Pragma("loopbound min DIM max DIM")
		for(i = 0; i < side; i++) {
			if(i != k) {
				w = minver_a[ i ][ k ];
				if(w != 0.0) {
					_Pragma("loopbound min DIM max DIM")
					for(j = 0; j < side; j++) {
						if(j != k) minver_a[ i ][ j ] -= w * minver_a[ k ][ j ];
					}
					minver_a[ i ][ k ] = -w / pivot;

				}
			}
		}
		minver_a[ k ][ k ] = 1.0 / pivot;
	}
	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < side;) {
		/*  The following redundant statement is inserted due to limitations of
			WCC's flow fact manager. It is required in order to have the flow
			fact pragma below uniquely attached to the while(1) loop.
		*/
		i = i;
		_Pragma("loopbound min 1 max DIM")
		while(1) {
			k = work[ i ];
			if(k == i) break;
			iw = work[ k ];
			work[ k ] = work[ i ];
			work[ i ] = iw;
			_Pragma("loopbound min DIM max DIM")
			for(j = 0; j < side; j++) {
				w = minver_a [k ][ i ];
				minver_a[ k ][ i ] = minver_a[ k ][ k ];
				minver_a[ k ][ k ] = w;
			}
		}
		i++;
	}
	minver_det = w1;
	return (0);

}

/*
	Main functions
*/

int main(void)
{

	float minver_a[DIM][DIM];

	float eps = 1.0e-6;
	set_minver(minver_a);

#if(WCET)

	minver_minver(minver_a, DIM, eps);

#else

	unsigned long long start_cycle, stop_cycle, return_cycles = 0;

	printf("Benchmarking \n");

	start_cycle = get_cpu_cycles();

	minver_minver(minver_a, DIM, eps);

	stop_cycle = get_cpu_cycles();
	return_cycles = stop_cycle-start_cycle-CYCLE_CALIBRATION;

	print_benchmark(return_cycles, 0);

#endif

	return 0;
}