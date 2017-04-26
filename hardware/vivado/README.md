# Folder Description

# Status

The status is whether it has been synthesised and tested on the FPGA board.
Please remember to ensure that the number of banks and the memory size is properly set in HWA_PACKAGE.vhd
and that the dimensions are correct in the hwa_lib.h file

## Matmul (Ports for each array)

### Float

- [x] matmul_float_3b_4x4
- [x] matmul_float_3b_16x16
- [x] matmul_float_3b_32x32
- [] matmul_float_5b_4x4
- [] matmul_float_5b_16x16
- [] matmul_float_5b_32x32
- [] matmul_float_7b_4x4
- [] matmul_float_7b_16x16
- [] matmul_float_7b_32x32

### Int

- [] matmul_int_3b_4x4
- [] matmul_int_3b_16x16
- [] matmul_int_3b_32x32
- [] matmul_int_5b_4x4
- [] matmul_int_5b_16x16
- [] matmul_int_5b_32x32
- [] matmul_int_7b_4x4
- [] matmul_int_7b_16x16
- [] matmul_int_7b_32x32

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

## Filterbank

### Float


# Using Vivado

There does occur some bugs from time to time, here are some ways of fixing them.

* Vivado stalls at synthesis.
	* One possible workaround is to ensure that the number of jobs selected is correct.
	* Another workaround is to not use the gui, but run vivado from batch mode "vivado -mode batch -source synth.tcl".

* Loading a package in
	* See [link](https://forums.xilinx.com/t5/Simulation-and-Verification/VHDL-package-not-comiled-in-work-library-gt-Vivado-2013-3/td-p/410645) and [link](https://forums.xilinx.com/t5/7-Series-FPGAs/A-VHDL-package-in-Vivado/td-p/660301)

* Warnings
	* WARNING: [Labtools 27-3123] The debug hub core was not detected at User Scan Chain 1 or 3. This warning can be safelyignored if we do not actually use any debug cores.