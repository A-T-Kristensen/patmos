/*
	This header file contains a number of useful definitions
	for using peripherals accessible in the local address space
	of Patmos. 

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: DTU, BSD License

 */

#ifndef HWA_DEF_H_
#define HWA_DEF_H_

#define ADDR_BITS 			16

#define LED_RUN_LENGTH 		2000
#define LED_ROUNDS			1

#define CYCLE_CALIBRATION 	3

#define BRAM_BASE 			0xF00B0000
#define HWA_CTRL_BASE 		0xF00C0000
#define LED_BASE 			0xF0090000


#endif /* __HWA_DEF_H__ */
