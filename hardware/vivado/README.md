# Folder Description

# Status

The status is whether it has been synthesised and tested on the FPGA board (with the C code).
Please remember to ensure that the dimensions are correct in the hwa_lib.h file (done automatically when using benchmark.py).

## Matmul (Ports for each array)

### Float

- [x] matmul_float_3b_4x4
- [x] matmul_float_3b_16x16
- [x] matmul_float_3b_32x32
- [x] matmul_float_5b_4x4
- [x] matmul_float_5b_16x16
- [x] matmul_float_5b_32x32
- [x] matmul_float_9b_4x4
- [x] matmul_float_9b_16x16
- [x] matmul_float_9b_32x32

### Int

- [x] matmul_int_3b_4x4
- [x] matmul_int_3b_16x16
- [x] matmul_int_3b_32x32
- [x] matmul_int_5b_4x4
- [x] matmul_int_5b_16x16
- [x] matmul_int_5b_32x32
- [x] matmul_int_9b_4x4
- [x] matmul_int_9b_16x16
- [x] matmul_int_9b_32x32

## Matmul (Elements in same array)

### Float

- [] matmul_misc_float_1b_4x4
- [] matmul_misc_float_1b_16x16
- [] matmul_misc_float_1b_32x32
- [] matmul_misc_float_2b_4x4
- [] matmul_misc_float_2b_16x16
- [] matmul_misc_float_2b_32x32
- [] matmul_misc_float_3b_4x4
- [] matmul_misc_float_3b_16x16
- [] matmul_misc_float_3b_32x32

### Int

- [] matmul_misc_int_1b_4x4
- [] matmul_misc_int_1b_16x16
- [] matmul_misc_int_1b_32x32
- [] matmul_misc_int_2b_4x4
- [] matmul_misc_int_2b_16x16
- [] matmul_misc_int_2b_32x32
- [] matmul_misc_int_3b_4x4
- [] matmul_misc_int_3b_16x16
- [] matmul_misc_int_3b_32x32

## Minver

### Float

- [] minver_float_1b_4x4
- [] minver_float_1b_16x16
- [] minver_float_1b_32x32
- [] minver_float_2b_4x4
- [] minver_float_2b_16x16
- [] minver_float_2b_32x32
- [] minver_float_4b_4x4
- [] minver_float_4b_16x16
- [] minver_float_4b_32x32

## Filterbank

### Float


## Fir2Dim

### Float

## SHA

## Md5

# Using Vivado

There does occur some bugs from time to time, here are some ways of fixing them.

* Vivado stalls at synthesis.
	* One possible workaround is to ensure that the number of jobs selected is correct.
	* Another workaround is to not use the gui, but run vivado from batch mode "vivado -mode batch -source synth.tcl".

* Loading a package in
	* See [link](https://forums.xilinx.com/t5/Simulation-and-Verification/VHDL-package-not-comiled-in-work-library-gt-Vivado-2013-3/td-p/410645) and [link](https://forums.xilinx.com/t5/7-Series-FPGAs/A-VHDL-package-in-Vivado/td-p/660301)

* Warnings
	* WARNING: [Labtools 27-3123] The debug hub core was not detected at User Scan Chain 1 or 3. This warning can be safelyignored if we do not actually use any debug cores.