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
ExecStep $xv_path/bin/xsim patmos_top_behav -key {Behavioral:sim_1:Functional:patmos_top} -tclbatch patmos_top.tcl -log simulate.log
