
# Do file for list_multiply c program testing a minimal working example
# of a HwA built using Vivado HLS for patmos.

vsim work.patmos_top

# Restart simulation and remove waves

restart -f -nowave

config wave -signalnamewidth 1

# Add inputs

add wave clk

add wave oLedsPins_led

add wave bramCtrl_Mcmd
add wave bramCtrl_MAddr
add wave bramCtrl_MData
add wave bramCtrl_MByteEn
add wave bramCtrl_SData

add wave hwACtrl_ap_start_out
add wave hwACtrl_ap_reset_out
add wave hwACtrl_ap_ready_in
add wave hwACtrl_ap_idle_in
add wave hwACtrl_ap_done_in

add wave hwa_we
add wave hwa_addr
add wave hwa_in
add wave hwa_out

# Set clock, period = 10 ns

force -freeze clk 0 0, 1 {5 ns} -r 10

# Run until we start seeing the outpus

run 1500