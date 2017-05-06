/*
    This is a minimal C program used for WCET test for writing to 
    the bram.
    
    Author: Andreas T. Kristensen 
    Copyright: DTU, BSD License
*/

// Files required for memory mapped IO devices
// patmos.h defines _IODEV, used to access memory mapped IO devices.

#include <machine/patmos.h> 

#define DIM 10

void bram_main( void ) __attribute__((noinline));

void _Pragma ( "entrypoint" ) bram_main(void){

	volatile _IODEV int *bram_ptr = (volatile _IODEV int *) 0xF00B0000;
	
	int i;
	int temp[DIM];

	// Write data to BRAM
	_Pragma( "loopbound min DIM max DIM" )
	for(i = 0; i < DIM; i++)
	{
		*(bram_ptr + i) = i + 1;
	}
	
	// Read back data from BRAM
	_Pragma( "loopbound min DIM max DIM" )
	for(i = 0; i < DIM; i++)
	{
		temp[i] = *(bram_ptr + i);
	}
}


int main() 
{
	bram_main();
	return 0;
}

