// Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
module patmos_top(clk_in, cpu_reset_btn, green_leds, rgb_leds, 
  seven_segments, seven_segments_drive, buttons, switches, uart_txd, uart_rxd, ddr2_dq, 
  ddr2_dqs_n, ddr2_dqs_p, ddr2_addr, ddr2_ba, ddr2_ras_n, ddr2_cas_n, ddr2_we_n, ddr2_ck_p, 
  ddr2_ck_n, ddr2_cke, ddr2_cs_n, ddr2_dm, ddr2_odt);
  input clk_in;
  input cpu_reset_btn;
  output [15:0]green_leds;
  output [5:0]rgb_leds;
  output [7:0]seven_segments;
  output [7:0]seven_segments_drive;
  input [4:0]buttons;
  input [15:0]switches;
  input uart_txd;
  output uart_rxd;
  inout [15:0]ddr2_dq;
  inout [1:0]ddr2_dqs_n;
  inout [1:0]ddr2_dqs_p;
  output [12:0]ddr2_addr;
  output [2:0]ddr2_ba;
  output ddr2_ras_n;
  output ddr2_cas_n;
  output ddr2_we_n;
  output [0:0]ddr2_ck_p;
  output [0:0]ddr2_ck_n;
  output [0:0]ddr2_cke;
  output [0:0]ddr2_cs_n;
  output [1:0]ddr2_dm;
  output [0:0]ddr2_odt;
endmodule
