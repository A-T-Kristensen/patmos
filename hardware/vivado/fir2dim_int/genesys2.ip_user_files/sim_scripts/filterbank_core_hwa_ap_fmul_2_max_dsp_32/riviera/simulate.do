onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+filterbank_core_hwa_ap_fmul_2_max_dsp_32 -L xil_defaultlib -L xpm -L xbip_utils_v3_0_7 -L axi_utils_v2_0_3 -L xbip_pipe_v3_0_3 -L xbip_dsp48_wrapper_v3_0_4 -L xbip_dsp48_addsub_v3_0_3 -L xbip_dsp48_multadd_v3_0_3 -L xbip_bram18k_v3_0_3 -L mult_gen_v12_0_12 -L floating_point_v7_1_3 -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.filterbank_core_hwa_ap_fmul_2_max_dsp_32 xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {filterbank_core_hwa_ap_fmul_2_max_dsp_32.udo}

run -all

endsim

quit -force
