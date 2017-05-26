/*
	This c file contains the functions used in testing
	whether the HwA result is correct.

	Author: Andreas T. Kristensen (s144026@student.dtu.dk)
	Copyright: DTU, BSD License
	
 */

#include "hwa_test.h"

int compare_arrays(mat_type hw_result[ROWS][COLS], 
				   mat_type sw_result[ROWS][COLS]) {

	int i, j, err_cnt = 0;

	_Pragma("loopbound min ROWS max ROWS")
	for(i = 0; i < ROWS; i++){
		_Pragma("loopbound min COLS max COLS")		
		for(j = 0; j < COLS; j++){
			if(hw_result[i][j] != sw_result[i][j]) {
				err_cnt++;
			}
		}
	}

	if(!err_cnt) {
		puts("Results correct");			
	} 

	else {
		puts("Results incorrect"); 
	}

	return err_cnt;
}

int compare_arrays_spm(volatile _SPM mat_type (*hw_result)[ROWS][COLS], 
					   mat_type sw_result[ROWS][COLS]) {

	int i, j, err_cnt = 0;

	_Pragma("loopbound min ROWS max ROWS")
	for(i = 0; i < ROWS; i++){
		_Pragma("loopbound min COLS max COLS")		
		for(j = 0; j < COLS; j++){
			if((*hw_result)[i][j] != sw_result[i][j]) {
				err_cnt++;	
			}
		}
	}

	if(!err_cnt) {
		puts("Results correct");			
	} 
	else {
		puts("Results incorrect"); 
	}

	return err_cnt;
}

int compare_arrays_uncached(volatile _UNCACHED mat_type (*hw_result)[ROWS][COLS], 
						  	mat_type sw_result[ROWS][COLS]) {

	int i, j, err_cnt = 0;

	_Pragma("loopbound min ROWS max ROWS")
	for(i = 0; i < ROWS; i++){
		_Pragma("loopbound min COLS max COLS")		
		for(j = 0; j < COLS; j++){
			if((*hw_result)[i][j] != sw_result[i][j]) {
				err_cnt++;	
			}
		}
	}

	if(!err_cnt) {
		puts("Results correct");			
	} 
	else {
		puts("Results incorrect"); 
	}

	return err_cnt;
}

int compare_vectors(mat_type hw_result[], 
					mat_type sw_result[],
					int length) {

	int i, err_cnt = 0;

	_Pragma("loopbound min VECSIZE max VECSIZE")
	for(i = 0; i < length; i++){
		if(hw_result[i] != sw_result[i]) {
			err_cnt++;	
		}
	}

	if(!err_cnt) {
		puts("Results correct");			
	} 
	
	else {
		puts("Results incorrect"); 
	}

	return err_cnt;
}

int compare_vectors_spm(volatile _SPM mat_type (*hw_result)[], 
						volatile _SPM mat_type (*sw_result)[],
						int length) {

	int i, err_cnt = 0;

	_Pragma("loopbound min VECSIZE max VECSIZE")
	for(i = 0; i < length; i++){
		if((*hw_result)[i] != (*sw_result)[i]) {
			err_cnt++;	
		}
	}

	if(!err_cnt) {
		puts("Results correct");			
	} 
	else {
		puts("Results incorrect"); 
	}

	return err_cnt;
}

int compare_vectors_uncached(volatile _UNCACHED mat_type (*hw_result)[], 
							 volatile _UNCACHED mat_type (*sw_result)[],
							 int length) {

	int i, err_cnt = 0;

	_Pragma("loopbound min VECSIZE max VECSIZE")
	for(i = 0; i < length; i++){
		if((*hw_result)[i] != (*sw_result)[i]) {
			err_cnt++;	
		}
	}

	if(!err_cnt) {
		puts("Results correct");			
	} 
	else {
		puts("Results incorrect"); 
	}

	return err_cnt;
}

void led_blink(int err_cnt) {

	volatile _IODEV int *led_ptr  = (volatile _IODEV int *) LED_BASE;
	int i, j;

	if(!err_cnt) {
		for (i = 0; i < LED_ROUNDS; i++) {
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 3;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
			
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 15;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
			
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 63;

			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;			
		}		
	} 

	else {
		for (i = 0; i < LED_ROUNDS; i++) {
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 0;
			
			for (i=LED_RUN_LENGTH; i!=0; --i)
				for (j=LED_RUN_LENGTH; j!=0; --j)
					*led_ptr = 7; 	
		}
	}
}

void print_benchmark(long long unsigned return_compute, 
					 long long unsigned return_transfer) {

	printf("<compute>%llu</compute>\n", return_compute);  
	printf("<transfer>%llu</transfer>\n", return_transfer);  
}