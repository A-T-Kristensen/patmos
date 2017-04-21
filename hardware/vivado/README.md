# Using Vivado

There does occur some bugs from time to time, here are some ways of fixing them.

* Vivado stalls at synthesis.
	* One possible workaround is to ensure that the number of jobs selected is correct.
	* Another workaround is to not use the gui, but run vivado from batch mode "vivado -mode batch -source synth.tcl".

* Loading a package in
	* See [link](https://forums.xilinx.com/t5/Simulation-and-Verification/VHDL-package-not-comiled-in-work-library-gt-Vivado-2013-3/td-p/410645) and [link](https://forums.xilinx.com/t5/7-Series-FPGAs/A-VHDL-package-in-Vivado/td-p/660301)

* Warnings
	* WARNING: [Labtools 27-3123] The debug hub core was not detected at User Scan Chain 1 or 3. This warning can be safelyignored if we do not actually use any debug cores.