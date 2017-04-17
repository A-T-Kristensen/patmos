#!/bin/bash -f
xv_path="/home/patmos/Xilinx/Vivado/2016.4"
ExecStep()
{
"$@"
RETVAL=$?
if [ $RETVAL -ne 0 ]
then
exit $RETVAL
fi
}
ExecStep $xv_path/bin/xelab -wto 44437113ce5a4f4fa39914f3cfeb84af -m64 --debug typical --relax --mt 8 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip -L xpm --snapshot patmos_top_behav xil_defaultlib.patmos_top xil_defaultlib.glbl -log elaborate.log
