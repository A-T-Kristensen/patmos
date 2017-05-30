TCRESTHOMEDIR?=$(HOME)/t-crest
SAVEDIR?=$(CURDIR)/analysis

# PROJECT and FUNCTION should just go into a python script as arguments to
# make: "make PROJECT?=hwa_matmul wcet"

PROJECT?=tacle_adpcm_enc
FUNCTION?=adpcm_enc_main

#Delay to global memory per request in cycles
T_DELAY_CYCLES?=0
#Transfer size (burst size) of the global memory in bytes
B_SIZE?=16
# Transfer time shall be used for the memory timing
TRANS_CYCLES?=83

wcet-config: 
	platin pml-config \
	--target patmos-unknown-unknown-elf \
	-o $(TCRESTHOMEDIR)/patmos/tmp/$(PROJECT)config.pml \
	--tdelay $(T_DELAY_CYCLES) \
	--gtime $(TRANS_CYCLES) \
	--bsize $(B_SIZE)

wcet: wcet-config
	platin wcet \
	-i $(TCRESTHOMEDIR)/patmos/tmp/wcet-$(PROJECT).pml \
	--enable-wca \
	--disable-ait \
	--stats \
	--binary $(TCRESTHOMEDIR)/patmos/tmp/wcet-$(PROJECT).elf \
	-e $(FUNCTION) \
	-o $(SAVEDIR)/$(PROJECT).wca \
	--report $(SAVEDIR)/$(PROJECT)_wcet_report.txt \
-i $(TCRESTHOMEDIR)/patmos/tmp/$(PROJECT)config.pml