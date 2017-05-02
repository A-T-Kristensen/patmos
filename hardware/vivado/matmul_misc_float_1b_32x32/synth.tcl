# Xilinx Vivado TCL script form synthesis to bitstream generation.
# The runs run with 8 jobs, reduce it for old machines.
# Author: Luca Pezzarossa (lpez@dtu.dk)
#open_project matmul_float.xpr
open_project ./hardware/vivado/matmul_misc_float_1b_32x32/matmul_float.xpr
reset_project
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
close_project
