onbreak {quit -f}
onerror {quit -f}

vsim -voptargs="+acc" -t 1ps -L xil_defaultlib -L xpm -L unisims_ver -L unimacro_ver -L secureip -lib xil_defaultlib xil_defaultlib.minver_hwa_ap_fdiv_14_no_dsp_32 xil_defaultlib.glbl

do {wave.do}

view wave
view structure
view signals

do {minver_hwa_ap_fdiv_14_no_dsp_32.udo}

run -all

quit -force