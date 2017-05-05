# A simple Hello World WCET analysis example

all:
	patmos-clang -O2 -mserialize=matrix1.pml matrix1.c
	platin wcet -i matrix1.pml -b a.out -e matrix1_main --report


clean:
	- rm a.out
	- rm *.pml
	- rm *.out
	- rm *.png
	- rm *.asm


# Following comannds are optional/unused

show: all
	platin wcet -i matrix1.pml -b a.out -e matrix1_main -o wcet.pml
	platin visualize -i wcet.pml --show-timings=platin

dump:
	patmos-llvm-objdump -d a.out > x.asm

gen_pml:
	platin pml-config --target patmos-unknown-unknown-elf -o de2-115.pml


