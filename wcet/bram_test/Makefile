# A simple bram test for WCET

all:
	patmos-clang -O2 -mserialize=bram_main.pml ../../c/bram_wcet.c
	platin wcet -i bram_main.pml -b a.out -e bram_main --report report.txt

clean:
	- rm a.out
	- rm *.pml
	- rm *.out
	- rm *.png
	- rm *.asm


# Following comannds are optional/unused

show: all
	platin wcet -i bram_main.pml -b a.out -e bram_main -o wcet.pml
	platin visualize -i wcet.pml --show-timings=platin

dump:
	patmos-llvm-objdump -d a.out > x.asm

gen_pml:
	platin pml-config --target patmos-unknown-unknown-elf -o de2-115.pml