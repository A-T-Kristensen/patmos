# Simulating Patmos
*by Andreas T. Kristensen*

We can simulate the patmos CPU for the de2-115 board. 

The steps are as follows

1. Prepare a c program with the following in inclusions (also, note that it may not use any print statements)

```c
#include "include/patio.h"
#include "include/bootable.h"
```

2. Run make "BOOTAPP=bootable-<program name> comp gen", this generate "Patmos.v" in ~/t-crest/patmos/hardware/build. This file should be used for simulation.
3. Open Modelsim and include all the required files for the project, e.g. top-level VHDL file and HDL files for components.
4. Run simulation and set the clock. 

Please note that the top-level file should be modified, so that it does not use PLL, otherwise simulation may not work. See some of the examples in this folder.

Note also, that for the naming scheme, it is implicit that we are targeting the de2-115 board.

# Program Description

This folder contains the Patmos_<c-filename>.v and top-level files used to test in Modelsim. Other required files are contained in 

* Accelerators: Contained in the git project "~/bachelor\_project_HLS/hls".
* HDL Components: Contained in "~/t-crest/patmos/hardware/vhdl".
* C code: Contained in "~/t-crest/patmos/c".
* Chisel code: contained in "~/t-crest/patmos/hardware/src". 

The following is a description of the programs included for simulation

