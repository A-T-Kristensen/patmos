Simulating Patmos
============

The de2-70 and de2-115 can simply be simulated using (# Force clk with duty cycle of 50% and period of 10 ns.)

	force -freeze sim:/patmos_top/clk 0 0, 1 {5 ns} -r 10