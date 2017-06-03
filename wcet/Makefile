TCRESTHOMEDIR?=$(HOME)/t-crest
SAVEDIR?=$(CURDIR)/analysis

# PROJECT and FUNCTION should just go into a python script as arguments to
# make: "make PROJECT?=hwa_matmul wcet"

PROJECT?=hwa_filterbank_uncached
FUNCTION?=adpcm_enc_main

wcet-config: 
	platin pml-config \
	--target patmos-unknown-unknown-elf

wcet_report: wcet-config
	platin wcet \
	-i $(TCRESTHOMEDIR)/patmos/tmp/wcet-$(PROJECT).pml \
	--enable-wca \
	--disable-ait \
	--stats \
	--binary $(TCRESTHOMEDIR)/patmos/tmp/wcet-$(PROJECT).elf \
	-e $(FUNCTION) \
	-o $(SAVEDIR)/$(PROJECT).wca \
	--report $(SAVEDIR)/$(PROJECT)_wcet_report.txt

wcet: wcet-config
	platin wcet \
	-i $(TCRESTHOMEDIR)/patmos/tmp/wcet-$(PROJECT).pml \
	--enable-wca \
	--disable-ait \
	--stats \
	--binary $(TCRESTHOMEDIR)/patmos/tmp/wcet-$(PROJECT).elf \
	-e $(FUNCTION) \
	-o $(SAVEDIR)/$(PROJECT).wca