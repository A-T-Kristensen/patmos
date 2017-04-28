onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib minver_hwa_ap_ddiv_29_no_dsp_64_opt

do {wave.do}

view wave
view structure
view signals

do {minver_hwa_ap_ddiv_29_no_dsp_64.udo}

run -all

quit -force
