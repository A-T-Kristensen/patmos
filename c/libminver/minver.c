/*
  This c file contains the functions used to generate
  the correct results to check with that produced by the
  HwA.

  It is based on the "minver" benchmark from the TACLeBench
  benchmark suite (author Sung-Soo Lim.

  Author: Andreas T. Kristensen (s144026@student.dtu.dk)
  Copyright: BSD License

 */

/*
    This program is derived from the SNU-RT Benchmark Suite for Worst
    Case Timing Analysis by Sung-Soo Lim

    Original source: Turbo C Programming for Engineering by Hyun Soo Ahn
 */

#include "minver.h"

mat_type minver_fabs(mat_type n)
{
	mat_type f;

	if(n >= 0)
		f = n;
	else
		f = -n;
	return f;
}

int minver_minver(mat_type minver_a[DIM][DIM], int side, mat_type eps)
{

	int work[ 500 ], i, j, k, iw;
	int r = 0;
	mat_type w, wmax, pivot, api, w1;
	mat_type minver_det;

	if(side < 2 || side > 500 || eps <= 0.0)
		return (999);

	w1 = 1.0;
	_Pragma("loopbound min DIM max DIM")
	for(i = 0; i < side; i++)
		work[ i ] = i;

	_Pragma("loopbound min DIM max DIM")
	for(k = 0; k < side; k++) {
		wmax = 0.0;
		_Pragma("loopbound min DIM max DIM")
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