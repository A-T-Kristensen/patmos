proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000

start_step init_design
set ACTIVE_STEP init_design
set rc [catch {
  create_msg_db init_design.pb
  create_project -in_memory -part xc7a100tcsg324-1
  set_property board_part digilentinc.com:nexys4_ddr:part0:1.1 [current_project]
  set_property design_mode GateLvl [current_fileset]
  set_param project.singleFileAddWarning.threshold 0
  set_property webtalk.parent_dir /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.cache/wt [current_project]
  set_property parent.project_path /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.xpr [current_project]
  set_property ip_output_repo /home/patmos/t-crest/patmos/hardware/vivado/genesys2/genesys2.cache/ip [current_project]
  set_property ip_cache_permissions {read write} [current_project]
  set_property XPM_LIBRARIES XPM_CDC [current_project]
  add_files -quiet /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.runs/synth_1/patmos_top.dcp
  add_files -quiet /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/ddr2_ctrl/ddr2_ctrl.dcp
  set_property netlist_only true [get_files /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/ddr2_ctrl/ddr2_ctrl.dcp]
  add_files -quiet /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/clk_manager/clk_manager.dcp
  set_property netlist_only true [get_files /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/clk_manager/clk_manager.dcp]
  read_xdc -mode out_of_context -ref ddr2_ctrl /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/ddr2_ctrl/ddr2_ctrl/user_design/constraints/ddr2_ctrl_ooc.xdc
  set_property processing_order EARLY [get_files /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/ddr2_ctrl/ddr2_ctrl/user_design/constraints/ddr2_ctrl_ooc.xdc]
  read_xdc -ref ddr2_ctrl /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/ddr2_ctrl/ddr2_ctrl/user_design/constraints/ddr2_ctrl.xdc
  set_property processing_order EARLY [get_files /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/ddr2_ctrl/ddr2_ctrl/user_design/constraints/ddr2_ctrl.xdc]
  read_xdc -mode out_of_context -ref clk_manager -cells inst /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/clk_manager/clk_manager_ooc.xdc
  set_property processing_order EARLY [get_files /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/clk_manager/clk_manager_ooc.xdc]
  read_xdc -prop_thru_buffers -ref clk_manager -cells inst /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/clk_manager/clk_manager_board.xdc
  set_property processing_order EARLY [get_files /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/clk_manager/clk_manager_board.xdc]
  read_xdc -ref clk_manager -cells inst /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/clk_manager/clk_manager.xdc
  set_property processing_order EARLY [get_files /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.srcs/sources_1/ip/clk_manager/clk_manager.xdc]
  read_xdc /home/patmos/t-crest/patmos/hardware/vivado/matmul_float_par/matmul_float.xdc
  link_design -top patmos_top -part xc7a100tcsg324-1
  write_hwdef -file patmos_top.hwdef
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
  unset ACTIVE_STEP 
}

start_step opt_design
set ACTIVE_STEP opt_design
set rc [catch {
  create_msg_db opt_design.pb
  opt_design 
  write_checkpoint -force patmos_top_opt.dcp
  catch { report_drc -file patmos_top_drc_opted.rpt }
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
  unset ACTIVE_STEP 
}

start_step place_design
set ACTIVE_STEP place_design
set rc [catch {
  create_msg_db place_design.pb
  implement_debug_core 
  place_design 
  write_checkpoint -force patmos_top_placed.dcp
  catch { report_io -file patmos_top_io_placed.rpt }
  catch { report_utilization -file patmos_top_utilization_placed.rpt -pb patmos_top_utilization_placed.pb }
  catch { report_control_sets -verbose -file patmos_top_control_sets_placed.rpt }
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
  unset ACTIVE_STEP 
}

start_step route_design
set ACTIVE_STEP route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force patmos_top_routed.dcp
  catch { report_drc -file patmos_top_drc_routed.rpt -pb patmos_top_drc_routed.pb -rpx patmos_top_drc_routed.rpx }
  catch { report_methodology -file patmos_top_methodology_drc_routed.rpt -rpx patmos_top_methodology_drc_routed.rpx }
  catch { report_timing_summary -warn_on_violation -max_paths 10 -file patmos_top_timing_summary_routed.rpt -rpx patmos_top_timing_summary_routed.rpx }
  catch { report_power -file patmos_top_power_routed.rpt -pb patmos_top_power_summary_routed.pb -rpx patmos_top_power_routed.rpx }
  catch { report_route_status -file patmos_top_route_status.rpt -pb patmos_top_route_status.pb }
  catch { report_clock_utilization -file patmos_top_clock_utilization_routed.rpt }
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  write_checkpoint -force patmos_top_routed_error.dcp
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
  unset ACTIVE_STEP 
}

start_step write_bitstream
set ACTIVE_STEP write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  set_property XPM_LIBRARIES XPM_CDC [current_project]
  catch { write_mem_info -force patmos_top.mmi }
  write_bitstream -force -no_partial_bitfile patmos_top.bit 
  catch { write_sysdef -hwdef patmos_top.hwdef -bitfile patmos_top.bit -meminfo patmos_top.mmi -file patmos_top.sysdef }
  catch {write_debug_probes -quiet -force debug_nets}
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
  unset ACTIVE_STEP 
}

