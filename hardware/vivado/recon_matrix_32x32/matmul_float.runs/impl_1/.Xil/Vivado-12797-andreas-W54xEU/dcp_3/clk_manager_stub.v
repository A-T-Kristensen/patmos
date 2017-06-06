// Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module clk_manager(clk_out_1, clk_out_2, locked, clk_in);
  output clk_out_1;
  output clk_out_2;
  output locked;
  input clk_in;
endmodule
