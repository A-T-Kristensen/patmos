
# Do file for list_multiply c program

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

add wave bram_m_i
add wave bram_s_i

# Set clock, period = 10 ns

force -freeze clk 0 0, 1 {5 ns} -r 10

# Run until we start seeing the outpus

run 16000