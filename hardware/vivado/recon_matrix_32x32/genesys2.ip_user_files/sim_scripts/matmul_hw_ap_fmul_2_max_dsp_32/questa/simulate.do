onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib matmul_hw_ap_fmul_2_max_dsp_32_opt

do {wave.do}

view wave
view structure
view signals

do {matmul_hw_ap_fmul_2_max_dsp_32.udo}

run -all

quit -force
