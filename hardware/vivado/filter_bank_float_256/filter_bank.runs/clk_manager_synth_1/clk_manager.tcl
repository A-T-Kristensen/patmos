# 
# Synthesis run script generated by Vivado
# 

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
set_msg_config -msgmgr_mode ooc_run
create_project -in_memory -part xc7a100tcsg324-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.cache/wt [current_project]
set_property parent.project_path /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.xpr [current_project]
set_property XPM_LIBRARIES XPM_CDC [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property board_part digilentinc.com:nexys4_ddr:part0:1.1 [current_project]
set_property ip_output_repo /home/patmos/t-crest/patmos/hardware/vivado/genesys2/genesys2.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_ip -quiet /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager.xci
set_property is_locked true [get_files /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager.xci]

foreach dcp [get_files -quiet -all *.dcp] {
  set_property used_in_implementation false $dcp
}
read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]

set cached_ip [config_ip_cache -export -no_bom -use_project_ipc -dir /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.runs/clk_manager_synth_1 -new_name clk_manager -ip [get_ips clk_manager]]

if { $cached_ip eq {} } {

synth_design -top clk_manager -part xc7a100tcsg324-1 -mode out_of_context

#---------------------------------------------------------
# Generate Checkpoint/Stub/Simulation Files For IP Cache
#---------------------------------------------------------
catch {
 write_checkpoint -force -noxdef -rename_prefix clk_manager_ clk_manager.dcp

 set ipCachedFiles {}
 write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ clk_manager_stub.v
 lappend ipCachedFiles clk_manager_stub.v

 write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ clk_manager_stub.vhdl
 lappend ipCachedFiles clk_manager_stub.vhdl

 write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ clk_manager_sim_netlist.v
 lappend ipCachedFiles clk_manager_sim_netlist.v

 write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ clk_manager_sim_netlist.vhdl
 lappend ipCachedFiles clk_manager_sim_netlist.vhdl

 config_ip_cache -add -dcp clk_manager.dcp -move_files $ipCachedFiles -use_project_ipc -ip [get_ips clk_manager]
}

rename_ref -prefix_all clk_manager_

write_checkpoint -force -noxdef clk_manager.dcp

catch { report_utilization -file clk_manager_utilization_synth.rpt -pb clk_manager_utilization_synth.pb }

if { [catch {
  file copy -force /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.runs/clk_manager_synth_1/clk_manager.dcp /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager.dcp
} _RESULT ] } { 
  send_msg_id runtcl-3 error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
  error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
}

if { [catch {
  write_verilog -force -mode synth_stub /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_stub.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a Verilog synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  write_vhdl -force -mode synth_stub /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_stub.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a VHDL synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  write_verilog -force -mode funcsim /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_sim_netlist.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the Verilog functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

if { [catch {
  write_vhdl -force -mode funcsim /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_sim_netlist.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the VHDL functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}


} else {


if { [catch {
  file copy -force /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.runs/clk_manager_synth_1/clk_manager.dcp /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager.dcp
} _RESULT ] } { 
  send_msg_id runtcl-3 error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
  error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
}

if { [catch {
  file rename -force /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.runs/clk_manager_synth_1/clk_manager_stub.v /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_stub.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a Verilog synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  file rename -force /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.runs/clk_manager_synth_1/clk_manager_stub.vhdl /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_stub.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a VHDL synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}

if { [catch {
  file rename -force /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.runs/clk_manager_synth_1/clk_manager_sim_netlist.v /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_sim_netlist.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the Verilog functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

if { [catch {
  file rename -force /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.runs/clk_manager_synth_1/clk_manager_sim_netlist.vhdl /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_sim_netlist.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the VHDL functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

}; # end if cached_ip 

if {[file isdir /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/genesys2.ip_user_files/ip/clk_manager]} {
  catch { 
    file copy -force /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_stub.v /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/genesys2.ip_user_files/ip/clk_manager
  }
}

if {[file isdir /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/genesys2.ip_user_files/ip/clk_manager]} {
  catch { 
    file copy -force /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/filter_bank.srcs/sources_1/ip/clk_manager/clk_manager_stub.vhdl /home/patmos/t-crest/patmos/hardware/vivado/filter_bank_float_256/genesys2.ip_user_files/ip/clk_manager
  }
}
