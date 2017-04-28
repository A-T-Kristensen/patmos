onbreak {quit -f}
onerror {quit -f}

vsim -voptargs="+acc" -t 1ps -L xil_defaultlib -L xpm -L xbip_utils_v3_0_7 -L axi_utils_v2_0_3 -L xbip_pipe_v3_0_3 -L xbip_dsp48_wrapper_v3_0_4 -L xbip_dsp48_addsub_v3_0_3 -L xbip_dsp48_multadd_v3_0_3 -L xbip_bram18k_v3_0_3 -L mult_gen_v12_0_12 -L floating_point_v7_1_3 -L unisims_ver -L unimacro_ver -L secureip -lib xil_defaultlib xil_defaultlib.matmul_hw_ap_fmul_2_max_dsp_32 xil_defaultlib.glbl

do {wave.do}

view wave
view structure
view signals

do {matmul_hw_ap_fmul_2_max_dsp_32.udo}

run -all

quit -force
