onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+minver_hwa_ap_fdiv_14_no_dsp_32 -L xil_defaultlib -L xpm -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.minver_hwa_ap_fdiv_14_no_dsp_32 xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {minver_hwa_ap_fdiv_14_no_dsp_32.udo}

run -all

endsim

quit -force