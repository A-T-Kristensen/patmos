
# Do file for test of communication between patmos and a BRAM.

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

# Set clock, period = 10 ns

force -freeze clk 0 0, 1 {5 ns} -r 10

# Run until we start seeing the outputs

run 4000