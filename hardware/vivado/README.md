# Folder Description

# Status

The status is whether it has been synthesised and tested on the FPGA board (with the C code).
Please remember to ensure that the dimensions are correct in the benchmark.h file (done automatically when using benchmark.py).

## ADPCM

### Int

- [] adpcm_mcu

## Filterbank

### Int

- [x] filterbank_int_mcu

## Fir2Dim

### Int

- [x] fir2dim_int_mcu

## Matmul (Ports for each array)

### Int

- [] matmul_int_3b_4x4_mcu
- [] matmul_int_3b_16x16_mcu
- [] matmul_int_3b_32x32_mcu
- [] matmul_int_5b_4x4_mcu
- [x] matmul_int_5b_16x16_mcu
- [x] matmul_int_5b_32x32_mcu
- [] matmul_int_9b_4x4_mcu
- [] matmul_int_9b_16x16_mcu
- [x] matmul_int_9b_32x32_mcu

# Using Vivado

There does occur some bugs from time to time, here are some ways of fixing them.

* Vivado stalls at synthesis.
	* A workaround is to not use the gui, but run vivado from batch mode "vivado -mode batch -source synth.tcl".

* Loading a package in
	* See [link](https://forums.xilinx.com/t5/Simulation-and-Verification/VHDL-package-not-comiled-in-work-library-gt-Vivado-2013-3/td-p/410645) and [link](https://forums.xilinx.com/t5/7-Series-FPGAs/A-VHDL-package-in-Vivado/td-p/660301)

* Warnings
	* WARNING: [Labtools 27-3123] The debug hub core was not detected at User Scan Chain 1 or 3. This warning can be safelyignored if we do not actually use any debug cores.