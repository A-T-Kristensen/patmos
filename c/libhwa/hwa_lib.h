/*
	This header file contains the required
	libraries for general use on Patmos.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: DTU, BSD License
	
 */


#ifndef HWA_LIB_H_
#define HWA_LIB_H_

#include <math.h>

#include <machine/spm.h> 	// Defines _SPM
#include <machine/patmos.h> // Defines _IODEV, used to access memory mapped IO devices.
#include <machine/rtc.h> 	// Gives us get_cpu_cycles

#include <stdio.h>
#include <stdlib.h> 

#include "benchmark.h"	// Contains parameters for benchmarks

#define ADDR_BITS 			16

#define LED_RUN_LENGTH 		2000
#define LED_ROUNDS			1

#define CYCLE_CALIBRATION 	3

#define BRAM_BASE 			0xF00B0000
#define HWA_CTRL_BASE 		0xF00C0000
#define LED_BASE 			0xF0090000


#endif /* __HWA_LIB_H__ */
