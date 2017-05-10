set_property SRC_FILE_INFO {cfile:/home/patmos/t-crest/patmos/hardware/vivado/filterbank_float_256/filterbank.srcs/sources_1/ip/ddr2_ctrl/ddr2_ctrl/user_design/constraints/ddr2_ctrl.xdc rfile:../../filterbank.srcs/sources_1/ip/ddr2_ctrl/ddr2_ctrl/user_design/constraints/ddr2_ctrl.xdc id:1 order:EARLY scoped_inst:ddr2_ctrl_inst_0 rxprname:$PSRCDIR/sources_1/ip/ddr2_ctrl/ddr2_ctrl/user_design/constraints/ddr2_ctrl.xdc} [current_design]
set_property SRC_FILE_INFO {cfile:/home/patmos/t-crest/patmos/hardware/vivado/filterbank_float_256/filterbank.srcs/sources_1/ip/clk_manager/clk_manager_board.xdc rfile:../../filterbank.srcs/sources_1/ip/clk_manager/clk_manager_board.xdc id:2 order:EARLY scoped_inst:clk_manager_inst_0/inst prop_thru_buffer:yes rxprname:$PSRCDIR/sources_1/ip/clk_manager/clk_manager_board.xdc} [current_design]
set_property SRC_FILE_INFO {cfile:/home/patmos/t-crest/patmos/hardware/vivado/filterbank_float_256/filterbank.srcs/sources_1/ip/clk_manager/clk_manager.xdc rfile:../../filterbank.srcs/sources_1/ip/clk_manager/clk_manager.xdc id:3 order:EARLY scoped_inst:clk_manager_inst_0/inst rxprname:$PSRCDIR/sources_1/ip/clk_manager/clk_manager.xdc} [current_design]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:CLKIN1:CLKFBOUT:clk_in:clkfbout_clk_manager::1:0:CLKIN1:CLKOUT0:clk_in:clk_out_1_clk_manager::1:0:CLKIN1:CLKOUT1:clk_in:clk_out_2_clk_manager::1:0:CLKIN1:CLKFBOUT:sys_clk_pin:clkfbout_clk_manager_1::1:0:CLKIN1:CLKOUT0:sys_clk_pin:clk_out_1_clk_manager_1::1:0:CLKIN1:CLKOUT1:sys_clk_pin:clk_out_2_clk_manager_1 [get_cells clk_manager_inst_0/inst/mmcm_adv_inst]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:CLKIN1:CLKFBOUT:pll_clk3_out:clk_pll_i::1:0:CLKIN1:CLKOUT0:pll_clk3_out:mmcm_ps_clk_bufg_in::1:0:CLKIN1:CLKOUT1:pll_clk3_out:clk_div2_bufg_in::1:0:CLKIN1:CLKFBOUT:pll_clk3_out_1:clk_pll_i_1::1:0:CLKIN1:CLKOUT0:pll_clk3_out_1:mmcm_ps_clk_bufg_in_1::1:0:CLKIN1:CLKOUT1:pll_clk3_out_1:clk_div2_bufg_in_1 [get_cells ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_ddr2_infrastructure/gen_mmcm.mmcm_i]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:CLKIN1:CLKFBOUT:clk_out_1_clk_manager:pll_clkfbout::1:0:CLKIN1:CLKOUT0:clk_out_1_clk_manager:freq_refclk::1:0:CLKIN1:CLKOUT1:clk_out_1_clk_manager:mem_refclk::1:0:CLKIN1:CLKOUT2:clk_out_1_clk_manager:sync_pulse::1:0:CLKIN1:CLKOUT3:clk_out_1_clk_manager:pll_clk3_out::1:0:CLKIN1:CLKFBOUT:clk_out_1_clk_manager_1:pll_clkfbout_1::1:0:CLKIN1:CLKOUT0:clk_out_1_clk_manager_1:freq_refclk_1::1:0:CLKIN1:CLKOUT1:clk_out_1_clk_manager_1:mem_refclk_1::1:0:CLKIN1:CLKOUT2:clk_out_1_clk_manager_1:sync_pulse_1::1:0:CLKIN1:CLKOUT3:clk_out_1_clk_manager_1:pll_clk3_out_1 [get_cells ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_ddr2_infrastructure/plle2_i]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:FREQREFCLK:ICLK:freq_refclk:u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/iserdes_clk::1:0:ICLK:ICLKDIV:u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/iserdes_clk:iserdes_clkdiv::1:0:FREQREFCLK:ICLK:freq_refclk_1:u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/iserdes_clk_1::1:0:ICLK:ICLKDIV:u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/iserdes_clk_1:iserdes_clkdiv_2 [get_cells ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/phaser_in_gen.phaser_in]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:MEMREFCLK:OCLK:mem_refclk:oserdes_clk::1:0:OCLK:OCLKDIV:oserdes_clk:oserdes_clkdiv::1:0:MEMREFCLK:OCLK:mem_refclk_1:oserdes_clk_4::1:0:OCLK:OCLKDIV:oserdes_clk_4:oserdes_clkdiv_4 [get_cells ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/phaser_out]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:MEMREFCLK:OCLK:mem_refclk:oserdes_clk_1::1:0:OCLK:OCLKDIV:oserdes_clk_1:oserdes_clkdiv_1::1:0:MEMREFCLK:OCLK:mem_refclk_1:oserdes_clk_5::1:0:OCLK:OCLKDIV:oserdes_clk_5:oserdes_clkdiv_5 [get_cells ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_B.ddr_byte_lane_B/phaser_out]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:FREQREFCLK:ICLK:freq_refclk:u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/iserdes_clk::1:0:ICLK:ICLKDIV:u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/iserdes_clk:iserdes_clkdiv_1::1:0:FREQREFCLK:ICLK:freq_refclk_1:u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/iserdes_clk_1::1:0:ICLK:ICLKDIV:u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/iserdes_clk_1:iserdes_clkdiv_3 [get_cells ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/phaser_in_gen.phaser_in]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:MEMREFCLK:OCLK:mem_refclk:oserdes_clk_2::1:0:OCLK:OCLKDIV:oserdes_clk_2:oserdes_clkdiv_2::1:0:MEMREFCLK:OCLK:mem_refclk_1:oserdes_clk_6::1:0:OCLK:OCLKDIV:oserdes_clk_6:oserdes_clkdiv_6 [get_cells ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/phaser_out]
set_property src_info {type:PI file:{} line:-1 export:NONE save:INPUT read:READ} [current_design]
set_property TOOL_DERIVED_CLK_NAMES 1:0:MEMREFCLK:OCLK:mem_refclk:oserdes_clk_3::1:0:OCLK:OCLKDIV:oserdes_clk_3:oserdes_clkdiv_3::1:0:MEMREFCLK:OCLK:mem_refclk_1:oserdes_clk_7::1:0:OCLK:OCLKDIV:oserdes_clk_7:oserdes_clkdiv_7 [get_cells ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_memc_ui_top_std/mem_intfc0/ddr_phy_top0/u_ddr_mc_phy_wrapper/u_ddr_mc_phy/ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_D.ddr_byte_lane_D/phaser_out]
set_property src_info {type:SCOPED_XDC file:1 line:1 export:INPUT save:INPUT read:READ} [current_design]
##################################################################################################
set_property src_info {type:SCOPED_XDC file:1 line:2 export:INPUT save:INPUT read:READ} [current_design]
##
set_property src_info {type:SCOPED_XDC file:1 line:3 export:INPUT save:INPUT read:READ} [current_design]
##  Xilinx, Inc. 2010            www.xilinx.com
set_property src_info {type:SCOPED_XDC file:1 line:4 export:INPUT save:INPUT read:READ} [current_design]
##  Thu Apr 27 21:16:53 2017
set_property src_info {type:SCOPED_XDC file:1 line:5 export:INPUT save:INPUT read:READ} [current_design]
##  Generated by MIG Version 4.0
set_property src_info {type:SCOPED_XDC file:1 line:6 export:INPUT save:INPUT read:READ} [current_design]
##
set_property src_info {type:SCOPED_XDC file:1 line:7 export:INPUT save:INPUT read:READ} [current_design]
##################################################################################################
set_property src_info {type:SCOPED_XDC file:1 line:8 export:INPUT save:INPUT read:READ} [current_design]
##  File name :       ddr2_ctrl.xdc
set_property src_info {type:SCOPED_XDC file:1 line:9 export:INPUT save:INPUT read:READ} [current_design]
##  Details :     Constraints file
set_property src_info {type:SCOPED_XDC file:1 line:10 export:INPUT save:INPUT read:READ} [current_design]
##                    FPGA Family:       ARTIX7
set_property src_info {type:SCOPED_XDC file:1 line:11 export:INPUT save:INPUT read:READ} [current_design]
##                    FPGA Part:         XC7A100T-CSG324
set_property src_info {type:SCOPED_XDC file:1 line:12 export:INPUT save:INPUT read:READ} [current_design]
##                    Speedgrade:        -1
set_property src_info {type:SCOPED_XDC file:1 line:13 export:INPUT save:INPUT read:READ} [current_design]
##                    Design Entry:      VERILOG
set_property src_info {type:SCOPED_XDC file:1 line:14 export:INPUT save:INPUT read:READ} [current_design]
##                    Frequency:         0 MHz
set_property src_info {type:SCOPED_XDC file:1 line:15 export:INPUT save:INPUT read:READ} [current_design]
##                    Time Period:       5000 ps
set_property src_info {type:SCOPED_XDC file:1 line:16 export:INPUT save:INPUT read:READ} [current_design]
##################################################################################################
set_property src_info {type:SCOPED_XDC file:1 line:17 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:18 export:INPUT save:INPUT read:READ} [current_design]
##################################################################################################
set_property src_info {type:SCOPED_XDC file:1 line:19 export:INPUT save:INPUT read:READ} [current_design]
## Controller 0
set_property src_info {type:SCOPED_XDC file:1 line:20 export:INPUT save:INPUT read:READ} [current_design]
## Memory Device: DDR2_SDRAM->Components->MT47H64M16HR-25E
set_property src_info {type:SCOPED_XDC file:1 line:21 export:INPUT save:INPUT read:READ} [current_design]
## Data Width: 16
set_property src_info {type:SCOPED_XDC file:1 line:22 export:INPUT save:INPUT read:READ} [current_design]
## Time Period: 5000
set_property src_info {type:SCOPED_XDC file:1 line:23 export:INPUT save:INPUT read:READ} [current_design]
## Data Mask: 1
set_property src_info {type:SCOPED_XDC file:1 line:24 export:INPUT save:INPUT read:READ} [current_design]
##################################################################################################
set_property src_info {type:SCOPED_XDC file:1 line:25 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:26 export:INPUT save:INPUT read:READ} [current_design]
#create_clock -period 5 [get_ports sys_clk_i]
set_property src_info {type:SCOPED_XDC file:1 line:27 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:28 export:INPUT save:INPUT read:READ} [current_design]
############## NET - IOSTANDARD ##################
set_property src_info {type:SCOPED_XDC file:1 line:29 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:30 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:31 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L23P_T3_34
set_property src_info {type:SCOPED_XDC file:1 line:32 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:33 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:34 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:35 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN R7 [get_ports {ddr2_dq[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:36 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:37 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L20N_T3_34
set_property src_info {type:SCOPED_XDC file:1 line:38 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:39 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:40 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:41 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V6 [get_ports {ddr2_dq[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:42 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:43 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L24P_T3_34
set_property src_info {type:SCOPED_XDC file:1 line:44 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:45 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:46 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:47 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN R8 [get_ports {ddr2_dq[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:48 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:49 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L22P_T3_34
set_property src_info {type:SCOPED_XDC file:1 line:50 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[3]}]
set_property src_info {type:SCOPED_XDC file:1 line:51 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[3]}]
set_property src_info {type:SCOPED_XDC file:1 line:52 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[3]}]
set_property src_info {type:SCOPED_XDC file:1 line:53 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U7 [get_ports {ddr2_dq[3]}]
set_property src_info {type:SCOPED_XDC file:1 line:54 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:55 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L20P_T3_34
set_property src_info {type:SCOPED_XDC file:1 line:56 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[4]}]
set_property src_info {type:SCOPED_XDC file:1 line:57 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[4]}]
set_property src_info {type:SCOPED_XDC file:1 line:58 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[4]}]
set_property src_info {type:SCOPED_XDC file:1 line:59 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V7 [get_ports {ddr2_dq[4]}]
set_property src_info {type:SCOPED_XDC file:1 line:60 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:61 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L19P_T3_34
set_property src_info {type:SCOPED_XDC file:1 line:62 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[5]}]
set_property src_info {type:SCOPED_XDC file:1 line:63 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[5]}]
set_property src_info {type:SCOPED_XDC file:1 line:64 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[5]}]
set_property src_info {type:SCOPED_XDC file:1 line:65 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN R6 [get_ports {ddr2_dq[5]}]
set_property src_info {type:SCOPED_XDC file:1 line:66 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:67 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L22N_T3_34
set_property src_info {type:SCOPED_XDC file:1 line:68 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[6]}]
set_property src_info {type:SCOPED_XDC file:1 line:69 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[6]}]
set_property src_info {type:SCOPED_XDC file:1 line:70 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[6]}]
set_property src_info {type:SCOPED_XDC file:1 line:71 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U6 [get_ports {ddr2_dq[6]}]
set_property src_info {type:SCOPED_XDC file:1 line:72 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:73 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L19N_T3_VREF_34
set_property src_info {type:SCOPED_XDC file:1 line:74 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[7]}]
set_property src_info {type:SCOPED_XDC file:1 line:75 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[7]}]
set_property src_info {type:SCOPED_XDC file:1 line:76 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[7]}]
set_property src_info {type:SCOPED_XDC file:1 line:77 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN R5 [get_ports {ddr2_dq[7]}]
set_property src_info {type:SCOPED_XDC file:1 line:78 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:79 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L12P_T1_MRCC_34
set_property src_info {type:SCOPED_XDC file:1 line:80 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[8]}]
set_property src_info {type:SCOPED_XDC file:1 line:81 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[8]}]
set_property src_info {type:SCOPED_XDC file:1 line:82 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[8]}]
set_property src_info {type:SCOPED_XDC file:1 line:83 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN T5 [get_ports {ddr2_dq[8]}]
set_property src_info {type:SCOPED_XDC file:1 line:84 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:85 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L8N_T1_34
set_property src_info {type:SCOPED_XDC file:1 line:86 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[9]}]
set_property src_info {type:SCOPED_XDC file:1 line:87 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[9]}]
set_property src_info {type:SCOPED_XDC file:1 line:88 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[9]}]
set_property src_info {type:SCOPED_XDC file:1 line:89 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U3 [get_ports {ddr2_dq[9]}]
set_property src_info {type:SCOPED_XDC file:1 line:90 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:91 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L10P_T1_34
set_property src_info {type:SCOPED_XDC file:1 line:92 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[10]}]
set_property src_info {type:SCOPED_XDC file:1 line:93 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[10]}]
set_property src_info {type:SCOPED_XDC file:1 line:94 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[10]}]
set_property src_info {type:SCOPED_XDC file:1 line:95 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V5 [get_ports {ddr2_dq[10]}]
set_property src_info {type:SCOPED_XDC file:1 line:96 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:97 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L8P_T1_34
set_property src_info {type:SCOPED_XDC file:1 line:98 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[11]}]
set_property src_info {type:SCOPED_XDC file:1 line:99 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[11]}]
set_property src_info {type:SCOPED_XDC file:1 line:100 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[11]}]
set_property src_info {type:SCOPED_XDC file:1 line:101 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U4 [get_ports {ddr2_dq[11]}]
set_property src_info {type:SCOPED_XDC file:1 line:102 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:103 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L10N_T1_34
set_property src_info {type:SCOPED_XDC file:1 line:104 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[12]}]
set_property src_info {type:SCOPED_XDC file:1 line:105 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[12]}]
set_property src_info {type:SCOPED_XDC file:1 line:106 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[12]}]
set_property src_info {type:SCOPED_XDC file:1 line:107 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V4 [get_ports {ddr2_dq[12]}]
set_property src_info {type:SCOPED_XDC file:1 line:108 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:109 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L12N_T1_MRCC_34
set_property src_info {type:SCOPED_XDC file:1 line:110 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[13]}]
set_property src_info {type:SCOPED_XDC file:1 line:111 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[13]}]
set_property src_info {type:SCOPED_XDC file:1 line:112 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[13]}]
set_property src_info {type:SCOPED_XDC file:1 line:113 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN T4 [get_ports {ddr2_dq[13]}]
set_property src_info {type:SCOPED_XDC file:1 line:114 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:115 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L7N_T1_34
set_property src_info {type:SCOPED_XDC file:1 line:116 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[14]}]
set_property src_info {type:SCOPED_XDC file:1 line:117 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[14]}]
set_property src_info {type:SCOPED_XDC file:1 line:118 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[14]}]
set_property src_info {type:SCOPED_XDC file:1 line:119 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V1 [get_ports {ddr2_dq[14]}]
set_property src_info {type:SCOPED_XDC file:1 line:120 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:121 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L11N_T1_SRCC_34
set_property src_info {type:SCOPED_XDC file:1 line:122 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dq[15]}]
set_property src_info {type:SCOPED_XDC file:1 line:123 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dq[15]}]
set_property src_info {type:SCOPED_XDC file:1 line:124 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dq[15]}]
set_property src_info {type:SCOPED_XDC file:1 line:125 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN T3 [get_ports {ddr2_dq[15]}]
set_property src_info {type:SCOPED_XDC file:1 line:126 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:127 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L18N_T2_34
set_property src_info {type:SCOPED_XDC file:1 line:128 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[12]}]
set_property src_info {type:SCOPED_XDC file:1 line:129 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[12]}]
set_property src_info {type:SCOPED_XDC file:1 line:130 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN N6 [get_ports {ddr2_addr[12]}]
set_property src_info {type:SCOPED_XDC file:1 line:131 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:132 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L5P_T0_34
set_property src_info {type:SCOPED_XDC file:1 line:133 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[11]}]
set_property src_info {type:SCOPED_XDC file:1 line:134 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[11]}]
set_property src_info {type:SCOPED_XDC file:1 line:135 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN K5 [get_ports {ddr2_addr[11]}]
set_property src_info {type:SCOPED_XDC file:1 line:136 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:137 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L15N_T2_DQS_34
set_property src_info {type:SCOPED_XDC file:1 line:138 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[10]}]
set_property src_info {type:SCOPED_XDC file:1 line:139 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[10]}]
set_property src_info {type:SCOPED_XDC file:1 line:140 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN R2 [get_ports {ddr2_addr[10]}]
set_property src_info {type:SCOPED_XDC file:1 line:141 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:142 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L13P_T2_MRCC_34
set_property src_info {type:SCOPED_XDC file:1 line:143 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[9]}]
set_property src_info {type:SCOPED_XDC file:1 line:144 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[9]}]
set_property src_info {type:SCOPED_XDC file:1 line:145 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN N5 [get_ports {ddr2_addr[9]}]
set_property src_info {type:SCOPED_XDC file:1 line:146 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:147 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L5N_T0_34
set_property src_info {type:SCOPED_XDC file:1 line:148 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[8]}]
set_property src_info {type:SCOPED_XDC file:1 line:149 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[8]}]
set_property src_info {type:SCOPED_XDC file:1 line:150 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN L4 [get_ports {ddr2_addr[8]}]
set_property src_info {type:SCOPED_XDC file:1 line:151 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:152 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L3N_T0_DQS_34
set_property src_info {type:SCOPED_XDC file:1 line:153 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[7]}]
set_property src_info {type:SCOPED_XDC file:1 line:154 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[7]}]
set_property src_info {type:SCOPED_XDC file:1 line:155 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN N1 [get_ports {ddr2_addr[7]}]
set_property src_info {type:SCOPED_XDC file:1 line:156 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:157 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L4N_T0_34
set_property src_info {type:SCOPED_XDC file:1 line:158 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[6]}]
set_property src_info {type:SCOPED_XDC file:1 line:159 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[6]}]
set_property src_info {type:SCOPED_XDC file:1 line:160 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN M2 [get_ports {ddr2_addr[6]}]
set_property src_info {type:SCOPED_XDC file:1 line:161 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:162 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L13N_T2_MRCC_34
set_property src_info {type:SCOPED_XDC file:1 line:163 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[5]}]
set_property src_info {type:SCOPED_XDC file:1 line:164 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[5]}]
set_property src_info {type:SCOPED_XDC file:1 line:165 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN P5 [get_ports {ddr2_addr[5]}]
set_property src_info {type:SCOPED_XDC file:1 line:166 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:167 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L2N_T0_34
set_property src_info {type:SCOPED_XDC file:1 line:168 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[4]}]
set_property src_info {type:SCOPED_XDC file:1 line:169 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[4]}]
set_property src_info {type:SCOPED_XDC file:1 line:170 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN L3 [get_ports {ddr2_addr[4]}]
set_property src_info {type:SCOPED_XDC file:1 line:171 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:172 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L17N_T2_34
set_property src_info {type:SCOPED_XDC file:1 line:173 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[3]}]
set_property src_info {type:SCOPED_XDC file:1 line:174 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[3]}]
set_property src_info {type:SCOPED_XDC file:1 line:175 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN T1 [get_ports {ddr2_addr[3]}]
set_property src_info {type:SCOPED_XDC file:1 line:176 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:177 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L18P_T2_34
set_property src_info {type:SCOPED_XDC file:1 line:178 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:179 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:180 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN M6 [get_ports {ddr2_addr[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:181 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:182 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L14P_T2_SRCC_34
set_property src_info {type:SCOPED_XDC file:1 line:183 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:184 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:185 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN P4 [get_ports {ddr2_addr[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:186 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:187 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L16P_T2_34
set_property src_info {type:SCOPED_XDC file:1 line:188 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_addr[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:189 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_addr[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:190 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN M4 [get_ports {ddr2_addr[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:191 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:192 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L17P_T2_34
set_property src_info {type:SCOPED_XDC file:1 line:193 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_ba[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:194 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_ba[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:195 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN R1 [get_ports {ddr2_ba[2]}]
set_property src_info {type:SCOPED_XDC file:1 line:196 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:197 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L14N_T2_SRCC_34
set_property src_info {type:SCOPED_XDC file:1 line:198 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_ba[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:199 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_ba[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:200 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN P3 [get_ports {ddr2_ba[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:201 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:202 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L15P_T2_DQS_34
set_property src_info {type:SCOPED_XDC file:1 line:203 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_ba[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:204 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_ba[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:205 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN P2 [get_ports {ddr2_ba[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:206 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:207 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L16N_T2_34
set_property src_info {type:SCOPED_XDC file:1 line:208 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports ddr2_ras_n]
set_property src_info {type:SCOPED_XDC file:1 line:209 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports ddr2_ras_n]
set_property src_info {type:SCOPED_XDC file:1 line:210 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN N4 [get_ports ddr2_ras_n]
set_property src_info {type:SCOPED_XDC file:1 line:211 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:212 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L1P_T0_34
set_property src_info {type:SCOPED_XDC file:1 line:213 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports ddr2_cas_n]
set_property src_info {type:SCOPED_XDC file:1 line:214 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports ddr2_cas_n]
set_property src_info {type:SCOPED_XDC file:1 line:215 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN L1 [get_ports ddr2_cas_n]
set_property src_info {type:SCOPED_XDC file:1 line:216 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:217 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L3P_T0_DQS_34
set_property src_info {type:SCOPED_XDC file:1 line:218 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports ddr2_we_n]
set_property src_info {type:SCOPED_XDC file:1 line:219 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports ddr2_we_n]
set_property src_info {type:SCOPED_XDC file:1 line:220 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN N2 [get_ports ddr2_we_n]
set_property src_info {type:SCOPED_XDC file:1 line:221 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:222 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L1N_T0_34
set_property src_info {type:SCOPED_XDC file:1 line:223 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_cke[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:224 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_cke[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:225 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN M1 [get_ports {ddr2_cke[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:226 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:227 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L4P_T0_34
set_property src_info {type:SCOPED_XDC file:1 line:228 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_odt[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:229 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_odt[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:230 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN M3 [get_ports {ddr2_odt[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:231 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:232 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_0_34
set_property src_info {type:SCOPED_XDC file:1 line:233 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_cs_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:234 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_cs_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:235 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN K6 [get_ports {ddr2_cs_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:236 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:237 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L23N_T3_34
set_property src_info {type:SCOPED_XDC file:1 line:238 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dm[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:239 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dm[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:240 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN T6 [get_ports {ddr2_dm[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:241 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:242 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L7P_T1_34
set_property src_info {type:SCOPED_XDC file:1 line:243 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dm[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:244 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD SSTL18_II [get_ports {ddr2_dm[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:245 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U1 [get_ports {ddr2_dm[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:246 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:247 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L21P_T3_DQS_34
set_property src_info {type:SCOPED_XDC file:1 line:248 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dqs_p[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:249 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dqs_p[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:250 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD DIFF_SSTL18_II [get_ports {ddr2_dqs_p[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:252 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:253 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L21N_T3_DQS_34
set_property src_info {type:SCOPED_XDC file:1 line:254 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dqs_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:255 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dqs_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:256 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD DIFF_SSTL18_II [get_ports {ddr2_dqs_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:257 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U9 [get_ports {ddr2_dqs_p[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:257 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V9 [get_ports {ddr2_dqs_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:258 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:259 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L9P_T1_DQS_34
set_property src_info {type:SCOPED_XDC file:1 line:260 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dqs_p[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:261 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dqs_p[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:262 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD DIFF_SSTL18_II [get_ports {ddr2_dqs_p[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:264 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:265 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L9N_T1_DQS_34
set_property src_info {type:SCOPED_XDC file:1 line:266 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_dqs_n[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:267 export:INPUT save:INPUT read:READ} [current_design]
set_property IN_TERM UNTUNED_SPLIT_50 [get_ports {ddr2_dqs_n[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:268 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD DIFF_SSTL18_II [get_ports {ddr2_dqs_n[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:269 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN U2 [get_ports {ddr2_dqs_p[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:269 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN V2 [get_ports {ddr2_dqs_n[1]}]
set_property src_info {type:SCOPED_XDC file:1 line:270 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:271 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L6P_T0_34
set_property src_info {type:SCOPED_XDC file:1 line:272 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_ck_p[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:273 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD DIFF_SSTL18_II [get_ports {ddr2_ck_p[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:275 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:276 export:INPUT save:INPUT read:READ} [current_design]
# PadFunction: IO_L6N_T0_VREF_34
set_property src_info {type:SCOPED_XDC file:1 line:277 export:INPUT save:INPUT read:READ} [current_design]
set_property SLEW FAST [get_ports {ddr2_ck_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:278 export:INPUT save:INPUT read:READ} [current_design]
set_property IOSTANDARD DIFF_SSTL18_II [get_ports {ddr2_ck_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:279 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN L6 [get_ports {ddr2_ck_p[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:279 export:INPUT save:INPUT read:READ} [current_design]
set_property PACKAGE_PIN L5 [get_ports {ddr2_ck_n[0]}]
set_property src_info {type:SCOPED_XDC file:1 line:280 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:281 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:282 export:INPUT save:INPUT read:READ} [current_design]
set_property INTERNAL_VREF 0.9 [get_iobanks 34]
set_property src_info {type:SCOPED_XDC file:1 line:283 export:INPUT save:INPUT read:READ} [current_design]

current_instance ddr2_ctrl_inst_0
set_property src_info {type:SCOPED_XDC file:1 line:284 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PHASER_OUT_PHY_X1Y7 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_D.ddr_byte_lane_D/phaser_out}]
set_property src_info {type:SCOPED_XDC file:1 line:285 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PHASER_OUT_PHY_X1Y5 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_B.ddr_byte_lane_B/phaser_out}]
set_property src_info {type:SCOPED_XDC file:1 line:286 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PHASER_OUT_PHY_X1Y6 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/phaser_out}]
set_property src_info {type:SCOPED_XDC file:1 line:287 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PHASER_OUT_PHY_X1Y4 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/phaser_out}]
set_property src_info {type:SCOPED_XDC file:1 line:288 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:289 export:INPUT save:INPUT read:READ} [current_design]
## set_property LOC PHASER_IN_PHY_X1Y7 [get_cells  -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_D.ddr_byte_lane_D/phaser_in_gen.phaser_in}]
set_property src_info {type:SCOPED_XDC file:1 line:290 export:INPUT save:INPUT read:READ} [current_design]
## set_property LOC PHASER_IN_PHY_X1Y5 [get_cells  -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_B.ddr_byte_lane_B/phaser_in_gen.phaser_in}]
set_property src_info {type:SCOPED_XDC file:1 line:291 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PHASER_IN_PHY_X1Y6 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/phaser_in_gen.phaser_in}]
set_property src_info {type:SCOPED_XDC file:1 line:292 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PHASER_IN_PHY_X1Y4 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/phaser_in_gen.phaser_in}]
set_property src_info {type:SCOPED_XDC file:1 line:293 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:294 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:295 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:296 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC OUT_FIFO_X1Y7 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_D.ddr_byte_lane_D/out_fifo}]
set_property src_info {type:SCOPED_XDC file:1 line:297 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC OUT_FIFO_X1Y5 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_B.ddr_byte_lane_B/out_fifo}]
set_property src_info {type:SCOPED_XDC file:1 line:298 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC OUT_FIFO_X1Y6 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/out_fifo}]
set_property src_info {type:SCOPED_XDC file:1 line:299 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC OUT_FIFO_X1Y4 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/out_fifo}]
set_property src_info {type:SCOPED_XDC file:1 line:300 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:301 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC IN_FIFO_X1Y6 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/in_fifo_gen.in_fifo}]
set_property src_info {type:SCOPED_XDC file:1 line:302 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC IN_FIFO_X1Y4 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/in_fifo_gen.in_fifo}]
set_property src_info {type:SCOPED_XDC file:1 line:303 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:304 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PHY_CONTROL_X1Y1 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/phy_control_i}]
set_property src_info {type:SCOPED_XDC file:1 line:305 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:306 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PHASER_REF_X1Y1 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/phaser_ref_i}]
set_property src_info {type:SCOPED_XDC file:1 line:307 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:308 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC OLOGIC_X1Y81 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_C.ddr_byte_lane_C/ddr_byte_group_io/*slave_ts}]
set_property src_info {type:SCOPED_XDC file:1 line:309 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC OLOGIC_X1Y57 [get_cells -hier -filter {NAME =~ */ddr_phy_4lanes_0.u_ddr_phy_4lanes/ddr_byte_lane_A.ddr_byte_lane_A/ddr_byte_group_io/*slave_ts}]
set_property src_info {type:SCOPED_XDC file:1 line:310 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:311 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC PLLE2_ADV_X1Y1 [get_cells -hier -filter {NAME =~ */u_ddr2_infrastructure/plle2_i}]
set_property src_info {type:SCOPED_XDC file:1 line:312 export:INPUT save:INPUT read:READ} [current_design]
set_property LOC MMCME2_ADV_X1Y1 [get_cells -hier -filter {NAME =~ */u_ddr2_infrastructure/gen_mmcm.mmcm_i}]
set_property src_info {type:SCOPED_XDC file:1 line:313 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:314 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:315 export:INPUT save:INPUT read:READ} [current_design]
set_multicycle_path -setup -from [get_cells -hier -filter {NAME =~ */mc0/mc_read_idle_r_reg}] -to [get_cells -hier -filter {NAME =~ */input_[?].iserdes_dq_.iserdesdq}] 6
set_property src_info {type:SCOPED_XDC file:1 line:318 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:319 export:INPUT save:INPUT read:READ} [current_design]
set_multicycle_path -hold -from [get_cells -hier -filter {NAME =~ */mc0/mc_read_idle_r_reg}] -to [get_cells -hier -filter {NAME =~ */input_[?].iserdes_dq_.iserdesdq}] 5
set_property src_info {type:SCOPED_XDC file:1 line:322 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:323 export:INPUT save:INPUT read:READ} [current_design]
set_false_path -through [get_pins -filter {NAME =~ */DQSFOUND} -of [get_cells -hier -filter {REF_NAME == PHASER_IN_PHY}]]
set_property src_info {type:SCOPED_XDC file:1 line:324 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:325 export:INPUT save:INPUT read:READ} [current_design]
set_multicycle_path -setup -start -through [get_pins -filter {NAME =~ */OSERDESRST} -of [get_cells -hier -filter {REF_NAME == PHASER_OUT_PHY}]] 2
set_property src_info {type:SCOPED_XDC file:1 line:326 export:INPUT save:INPUT read:READ} [current_design]
set_multicycle_path -hold -start -through [get_pins -filter {NAME =~ */OSERDESRST} -of [get_cells -hier -filter {REF_NAME == PHASER_OUT_PHY}]] 1
set_property src_info {type:SCOPED_XDC file:1 line:327 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:328 export:INPUT save:INPUT read:READ} [current_design]
set_max_delay -datapath_only -from [get_cells -hier -filter {NAME =~ *temp_mon_enabled.u_tempmon/* && IS_SEQUENTIAL}] -to [get_cells -hier -filter {NAME =~ *temp_mon_enabled.u_tempmon/device_temp_sync_r1*}] 20.000
set_property src_info {type:SCOPED_XDC file:1 line:329 export:INPUT save:INPUT read:READ} [current_design]
set_max_delay -datapath_only -from [get_cells -hier *rstdiv0_sync_r1_reg*] -to [get_pins -filter {NAME =~ */RESET} -of [get_cells -hier -filter {REF_NAME == PHY_CONTROL}]] 5.000
set_property src_info {type:SCOPED_XDC file:1 line:330 export:INPUT save:INPUT read:READ} [current_design]
set_false_path -through [get_pins -hier -filter {NAME =~ */u_iodelay_ctrl/sys_rst}]
set_property src_info {type:SCOPED_XDC file:1 line:331 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:332 export:INPUT save:INPUT read:READ} [current_design]
set_max_delay -datapath_only -from [get_cells -hier -filter {NAME =~ *ddr2_infrastructure/rstdiv0_sync_r1_reg*}] -to [get_cells -hier -filter {NAME =~ *temp_mon_enabled.u_tempmon/xadc_supplied_temperature.rst_r1*}] 20.000
set_property src_info {type:SCOPED_XDC file:1 line:333 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:1 line:334 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:2 line:1 export:INPUT save:INPUT read:READ} [current_design]
#--------------------Physical Constraints-----------------
set_property src_info {type:SCOPED_XDC file:2 line:2 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:2 line:3 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:3 line:1 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:3 line:2 export:INPUT save:INPUT read:READ} [current_design]
# file: clk_manager.xdc
set_property src_info {type:SCOPED_XDC file:3 line:3 export:INPUT save:INPUT read:READ} [current_design]
#
set_property src_info {type:SCOPED_XDC file:3 line:4 export:INPUT save:INPUT read:READ} [current_design]
# (c) Copyright 2008 - 2013 Xilinx, Inc. All rights reserved.
set_property src_info {type:SCOPED_XDC file:3 line:5 export:INPUT save:INPUT read:READ} [current_design]
#
set_property src_info {type:SCOPED_XDC file:3 line:6 export:INPUT save:INPUT read:READ} [current_design]
# This file contains confidential and proprietary information
set_property src_info {type:SCOPED_XDC file:3 line:7 export:INPUT save:INPUT read:READ} [current_design]
# of Xilinx, Inc. and is protected under U.S. and
set_property src_info {type:SCOPED_XDC file:3 line:8 export:INPUT save:INPUT read:READ} [current_design]
# international copyright and other intellectual property
set_property src_info {type:SCOPED_XDC file:3 line:9 export:INPUT save:INPUT read:READ} [current_design]
# laws.
set_property src_info {type:SCOPED_XDC file:3 line:10 export:INPUT save:INPUT read:READ} [current_design]
#
set_property src_info {type:SCOPED_XDC file:3 line:11 export:INPUT save:INPUT read:READ} [current_design]
# DISCLAIMER
set_property src_info {type:SCOPED_XDC file:3 line:12 export:INPUT save:INPUT read:READ} [current_design]
# This disclaimer is not a license and does not grant any
set_property src_info {type:SCOPED_XDC file:3 line:13 export:INPUT save:INPUT read:READ} [current_design]
# rights to the materials distributed herewith. Except as
set_property src_info {type:SCOPED_XDC file:3 line:14 export:INPUT save:INPUT read:READ} [current_design]
# otherwise provided in a valid license issued to you by
set_property src_info {type:SCOPED_XDC file:3 line:15 export:INPUT save:INPUT read:READ} [current_design]
# Xilinx, and to the maximum extent permitted by applicable
set_property src_info {type:SCOPED_XDC file:3 line:16 export:INPUT save:INPUT read:READ} [current_design]
# law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
set_property src_info {type:SCOPED_XDC file:3 line:17 export:INPUT save:INPUT read:READ} [current_design]
# WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
set_property src_info {type:SCOPED_XDC file:3 line:18 export:INPUT save:INPUT read:READ} [current_design]
# AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
set_property src_info {type:SCOPED_XDC file:3 line:19 export:INPUT save:INPUT read:READ} [current_design]
# BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
set_property src_info {type:SCOPED_XDC file:3 line:20 export:INPUT save:INPUT read:READ} [current_design]
# INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
set_property src_info {type:SCOPED_XDC file:3 line:21 export:INPUT save:INPUT read:READ} [current_design]
# (2) Xilinx shall not be liable (whether in contract or tort,
set_property src_info {type:SCOPED_XDC file:3 line:22 export:INPUT save:INPUT read:READ} [current_design]
# including negligence, or under any other theory of
set_property src_info {type:SCOPED_XDC file:3 line:23 export:INPUT save:INPUT read:READ} [current_design]
# liability) for any loss or damage of any kind or nature
set_property src_info {type:SCOPED_XDC file:3 line:24 export:INPUT save:INPUT read:READ} [current_design]
# related to, arising under or in connection with these
set_property src_info {type:SCOPED_XDC file:3 line:25 export:INPUT save:INPUT read:READ} [current_design]
# materials, including for any direct, or any indirect,
set_property src_info {type:SCOPED_XDC file:3 line:26 export:INPUT save:INPUT read:READ} [current_design]
# special, incidental, or consequential loss or damage
set_property src_info {type:SCOPED_XDC file:3 line:27 export:INPUT save:INPUT read:READ} [current_design]
# (including loss of data, profits, goodwill, or any type of
set_property src_info {type:SCOPED_XDC file:3 line:28 export:INPUT save:INPUT read:READ} [current_design]
# loss or damage suffered as a result of any action brought
set_property src_info {type:SCOPED_XDC file:3 line:29 export:INPUT save:INPUT read:READ} [current_design]
# by a third party) even if such damage or loss was
set_property src_info {type:SCOPED_XDC file:3 line:30 export:INPUT save:INPUT read:READ} [current_design]
# reasonably foreseeable or Xilinx had been advised of the
set_property src_info {type:SCOPED_XDC file:3 line:31 export:INPUT save:INPUT read:READ} [current_design]
# possibility of the same.
set_property src_info {type:SCOPED_XDC file:3 line:32 export:INPUT save:INPUT read:READ} [current_design]
#
set_property src_info {type:SCOPED_XDC file:3 line:33 export:INPUT save:INPUT read:READ} [current_design]
# CRITICAL APPLICATIONS
set_property src_info {type:SCOPED_XDC file:3 line:34 export:INPUT save:INPUT read:READ} [current_design]
# Xilinx products are not designed or intended to be fail-
set_property src_info {type:SCOPED_XDC file:3 line:35 export:INPUT save:INPUT read:READ} [current_design]
# safe, or for use in any application requiring fail-safe
set_property src_info {type:SCOPED_XDC file:3 line:36 export:INPUT save:INPUT read:READ} [current_design]
# performance, such as life-support or safety devices or
set_property src_info {type:SCOPED_XDC file:3 line:37 export:INPUT save:INPUT read:READ} [current_design]
# systems, Class III medical devices, nuclear facilities,
set_property src_info {type:SCOPED_XDC file:3 line:38 export:INPUT save:INPUT read:READ} [current_design]
# applications related to the deployment of airbags, or any
set_property src_info {type:SCOPED_XDC file:3 line:39 export:INPUT save:INPUT read:READ} [current_design]
# other applications that could lead to death, personal
set_property src_info {type:SCOPED_XDC file:3 line:40 export:INPUT save:INPUT read:READ} [current_design]
# injury, or severe property or environmental damage
set_property src_info {type:SCOPED_XDC file:3 line:41 export:INPUT save:INPUT read:READ} [current_design]
# (individually and collectively, "Critical
set_property src_info {type:SCOPED_XDC file:3 line:42 export:INPUT save:INPUT read:READ} [current_design]
# Applications"). Customer assumes the sole risk and
set_property src_info {type:SCOPED_XDC file:3 line:43 export:INPUT save:INPUT read:READ} [current_design]
# liability of any use of Xilinx products in Critical
set_property src_info {type:SCOPED_XDC file:3 line:44 export:INPUT save:INPUT read:READ} [current_design]
# Applications, subject only to applicable laws and
set_property src_info {type:SCOPED_XDC file:3 line:45 export:INPUT save:INPUT read:READ} [current_design]
# regulations governing limitations on product liability.
set_property src_info {type:SCOPED_XDC file:3 line:46 export:INPUT save:INPUT read:READ} [current_design]
#
set_property src_info {type:SCOPED_XDC file:3 line:47 export:INPUT save:INPUT read:READ} [current_design]
# THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
set_property src_info {type:SCOPED_XDC file:3 line:48 export:INPUT save:INPUT read:READ} [current_design]
# PART OF THIS FILE AT ALL TIMES.
set_property src_info {type:SCOPED_XDC file:3 line:49 export:INPUT save:INPUT read:READ} [current_design]
#
set_property src_info {type:SCOPED_XDC file:3 line:50 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:3 line:51 export:INPUT save:INPUT read:READ} [current_design]
# Input clock periods. These duplicate the values entered for the
set_property src_info {type:SCOPED_XDC file:3 line:52 export:INPUT save:INPUT read:READ} [current_design]
# input clocks. You can use these to time your system. If required
set_property src_info {type:SCOPED_XDC file:3 line:53 export:INPUT save:INPUT read:READ} [current_design]
# commented constraints can be used in the top level xdc
set_property src_info {type:SCOPED_XDC file:3 line:54 export:INPUT save:INPUT read:READ} [current_design]
#----------------------------------------------------------------
set_property src_info {type:SCOPED_XDC file:3 line:55 export:INPUT save:INPUT read:READ} [current_design]
# Connect to input port when clock capable pin is selected for input
current_instance -quiet
set_property src_info {type:SCOPED_XDC file:3 line:56 export:INPUT save:INPUT read:READ} [current_design]
create_clock -period 10.000 [get_ports clk_in]
set_property src_info {type:SCOPED_XDC file:3 line:57 export:INPUT save:INPUT read:READ} [current_design]
set_input_jitter [get_clocks -of_objects [get_ports clk_in]] 0.100
set_property src_info {type:SCOPED_XDC file:3 line:58 export:INPUT save:INPUT read:READ} [current_design]

set_property src_info {type:SCOPED_XDC file:3 line:59 export:INPUT save:INPUT read:READ} [current_design]

current_instance clk_manager_inst_0/inst
set_property src_info {type:SCOPED_XDC file:3 line:60 export:INPUT save:INPUT read:READ} [current_design]
set_property PHASESHIFT_MODE WAVEFORM [get_cells -hierarchical *adv*]
set_property src_info {type:SCOPED_XDC file:3 line:61 export:INPUT save:INPUT read:READ} [current_design]

