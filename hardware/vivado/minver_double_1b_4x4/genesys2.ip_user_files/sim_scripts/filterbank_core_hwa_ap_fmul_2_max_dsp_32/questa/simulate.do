onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib filterbank_core_hwa_ap_fmul_2_max_dsp_32_opt

do {wave.do}

view wave
view structure
view signals

do {filterbank_core_hwa_ap_fmul_2_max_dsp_32.udo}

run -all

quit -force
