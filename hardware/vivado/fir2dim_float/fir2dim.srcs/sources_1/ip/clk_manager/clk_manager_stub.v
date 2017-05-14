// Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2016.4 (lin64) Build 1733598 Wed Dec 14 22:35:42 MST 2016
// Date        : Wed Mar  1 16:52:22 2017
// Host        : ubuntu running 64-bit Ubuntu 16.04.2 LTS
// Command     : write_verilog -force -mode synth_stub -rename_top clk_manager -prefix
//               clk_manager_ clk_manager_stub.v
// Design      : clk_manager
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module clk_manager(clk_out_1, clk_out_2, locked, clk_in)
/* synthesis syn_black_box black_box_pad_pin="clk_out_1,clk_out_2,locked,clk_in" */;
  output clk_out_1;
  output clk_out_2;
  output locked;
  input clk_in;
endmodule
