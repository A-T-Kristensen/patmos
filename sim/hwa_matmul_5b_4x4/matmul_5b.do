
# Do file for matrix multiplier c program
# using 2 memory banks

#vsim work.patmos_top
vsim {-voptargs=work.patmos_top +acc} work.patmos_top

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
add wave -position insertpoint sim:/patmos_top/comp/core/iocomp/BRamCtrl/io_ocp_S_Resp

add wave hwACtrl_ap_start_out
add wave hwACtrl_ap_reset_out
add wave hwACtrl_ap_ready_in
add wave hwACtrl_ap_idle_in
add wave hwACtrl_ap_done_in

add wave bram_m_i
add wave bram_s_i

add wave n_bank_inst_0/p_b_we
add wave n_bank_inst_0/p_bank_sel

add wave -position insertpoint sim:/patmos_top/comp/core/iocomp/BRamCtrl/settings

add wave -position insertpoint  \
sim:/patmos_top/comp/core/iocomp/BRamCtrl/state
add wave -position insertpoint  \
sim:/patmos_top/comp/core/iocomp/BRamCtrl/start_bank
add wave -position insertpoint  \
sim:/patmos_top/comp/core/iocomp/BRamCtrl/cur_bank
add wave -position insertpoint  \
sim:/patmos_top/comp/core/iocomp/BRamCtrl/rows
add wave -position insertpoint  \
sim:/patmos_top/comp/core/iocomp/BRamCtrl/row_cnt
add wave -position insertpoint  \
sim:/patmos_top/comp/core/iocomp/BRamCtrl/col_cnt
add wave -position insertpoint  \
sim:/patmos_top/comp/core/iocomp/BRamCtrl/max_bank


add wave -position insertpoint sim:/patmos_top/n_bank_inst_0/bram_gen(0)/bram_array/mem
add wave -position insertpoint sim:/patmos_top/n_bank_inst_0/bram_gen(1)/bram_array/mem
add wave -position insertpoint sim:/patmos_top/n_bank_inst_0/bram_gen(2)/bram_array/mem
add wave -position insertpoint sim:/patmos_top/n_bank_inst_0/bram_gen(3)/bram_array/mem
add wave -position insertpoint sim:/patmos_top/n_bank_inst_0/bram_gen(4)/bram_array/mem


# Set clock, period = 10 ns

force -freeze clk 0 0, 1 {5 ns} -r 10

# Run until we start seeing the outpus

run 16000