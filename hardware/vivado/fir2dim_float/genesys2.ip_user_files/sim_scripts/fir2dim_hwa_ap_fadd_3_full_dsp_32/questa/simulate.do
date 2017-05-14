onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib fir2dim_hwa_ap_fadd_3_full_dsp_32_opt

do {wave.do}

view wave
view structure
view signals

do {fir2dim_hwa_ap_fadd_3_full_dsp_32.udo}

run -all

quit -force
