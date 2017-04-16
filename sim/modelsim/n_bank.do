
# Restart simulation and remove waves

restart -f -nowave

config wave -signalnamewidth 1

# Add inputs

add wave clk

add wave p_we
add wave p_addr
add wave p_dout
add wave p_din

add wave hwa_out
add wave hwa_in

add wave p_b_we
add wave p_bank_sel
add wave p_bank_sel_next

add wave n_bank/bram_gen(0)/bram_array/mem(0)
add wave n_bank/bram_gen(1)/bram_array/mem(0)
add wave n_bank/bram_gen(2)/bram_array/mem(0)
add wave n_bank/bram_gen(3)/bram_array/mem(0)

# Set clock, period = 10 ns

force -freeze clk 0 0, 1 {5 ns} -r 10

# Force input signals to 0

# denote radix

force p_addr 16#0000
force p_we 0
force p_dout 16#00000000

force hwa_out(0).wr 0
force hwa_out(0).addr 16#000
force hwa_out(0).din 16#00000000

force hwa_out(1).wr 0
force hwa_out(1).addr 16#000
force hwa_out(1).din 16#00000000

force hwa_out(2).wr 0
force hwa_out(2).addr 16#000
force hwa_out(2).din 16#00000000

force hwa_out(3).wr 0
force hwa_out(3).addr 16#000
force hwa_out(3).din 16#00000000

# We start with a falling edge, so run for 5 extra

run 15

# Write to bank 0

force p_we 1
force p_dout 16#ffffffff

run 10

# Write to bank 1

force p_addr(14) 1
force p_we 1
force p_dout 16#cccccccc

run 10

# Write to bank 2

force p_addr(14) 0
force p_addr(15) 1
force p_we 1
force p_dout 16#bbbbbbbb

run 10

# Write to bank 3

force p_addr(14) 1
force p_we 1
force p_dout 16#aaaaaaaa

# Run 20 and check that we get FFFFFFF for Patmos
# and CCCCCCCC and FFFFFFF for hwa on both ports

run 20

# Write 0 to the addresses from the HwA and check that it goes to 0

force p_addr(14) 0
force p_addr(15) 0
force p_we 0
force p_dout 16#00000000

force hwa_out(0).wr 1
force hwa_out(0).addr 16#000
force hwa_out(0).din 16#00000000

force hwa_out(1).wr 1
force hwa_out(1).addr 16#000
force hwa_out(1).din 16#00000001

force hwa_out(2).wr 1
force hwa_out(2).addr 16#000
force hwa_out(2).din 16#00000002

force hwa_out(3).wr 1
force hwa_out(3).addr 16#000
force hwa_out(3).din 16#00000003

run 10

force hwa_out(0).wr 0
force hwa_out(1).wr 0
force hwa_out(2).wr 0
force hwa_out(3).wr 0

run 10