/*
    This is a minimal C program to exlore WCET analysis.
    foo() is the function to analyze and it is not obvious
    if the multiplication or the addition path is the WCET path.

    Author: Andreas T. Kristensen
    Copyright: DTU, BSD License
*/

// foo is the analysis entry point that would be inlined with -O2
int foo(int bar) __attribute__((noinline));
int foo(int bar)
{

	int i = 0;

	if(bar) {
		bar = bar * 20;

		if(bar > 100) {
			bar = 0;
		}
	} else {
		bar = 10;
	}

	return bar;
}


int main(int argc, char** argv)
{

	// The compiler will not compute the result
	volatile int seed = 20;

	int bar = seed/4;
	int i = foo(bar);

	return i;
}
