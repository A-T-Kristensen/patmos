# Using Vivado

There does occur some bugs from time to time, here are some ways of fixing them.

* Vivado stalls at synthesis.
	* One possible workaround is to ensure that the number of jobs selected is correct.
	* Another workaround is to not use the gui, but run vivado from batch mode "vivado -mode batch -source synth.tcl".