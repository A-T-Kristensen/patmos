
# Restart simulation and remove waves

restart -f -nowave

# Add inputs

add wave clk

add wave p_we
add wave p_addr
add wave p_dout
add wave p_din

add wave b1_wr
add wave b1_addr
add wave b1_din
add wave b1_dout

add wave b2_wr
add wave b2_addr
add wave b2_din
add wave b2_dout

add wave p_b1_we
add wave p_b2_we
add wave p_bank_sel
add wave p_b1_data
add wave p_b2_data

add wave bram_tdp_inst_0/mem(0)
add wave bram_tdp_inst_1/mem(0)

# Set clock, period = 10 ns

force -freeze clk 0 0, 1 {5 ns} -r 10

# Force input signals to 0

# denote radix

force p_addr 16#0000
force p_we 0
force p_dout 16#00000000

force b1_wr 0
force b1_addr 16#0000
force b1_din 16#00000000

force b2_wr 0
force b2_addr 16#00000000
force b2_din 16#00000000

# We start with a falling edge, so run for 5 extra

run 25

# Write into bank 1

force p_addr 16#0000
force p_we 1
force p_dout 16#ffffffff

run 10

force p_we 0
force p_dout 16#00000000

run 10

# Write into bank 2

force p_addr(15) 1
force p_we 1
force p_dout 16#cccccccc

run 10

force p_addr(15) 0
force p_we 0
force p_dout 16#00000000

run 20

# Read from bank 1

force p_addr 16#0000

run 10

# Read from bank 2

force p_addr(15) 1

run 10

force p_addr(15) 0

run 10

# Write into bank 2

force p_addr(15) 1
force p_we 1
force p_dout 16#ffffffff

run 10

force p_addr(15) 1
force p_we 0
force p_dout 16#00000000

run 20

force p_addr(15) 0

# Write into bank 1

force p_we 1
force p_dout 16#aaaaaaaa

run 10

force p_we 0
force p_dout 16#00000000

run 20
