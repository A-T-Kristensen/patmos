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

#include "hwa_def.h"
#include "benchmark.h"	// Contains parameters for benchmarks

#endif /* __HWA_LIB_H__ */
