## This file is a general .xdc for the Nexys4 DDR Rev. C
## To use it in a project:
## - uncomment the lines corresponding to used pins
## - rename the used ports (in each line, after get_ports) according to the top level signal names in the project

## Clock signal
set_property -dict {PACKAGE_PIN E3 IOSTANDARD LVCMOS33} [get_ports clk_in]
create_clock -period 10.000 -name sys_clk_pin -waveform {0.000 5.000} -add [get_ports clk_in]

#create_generated_clock -name 80_mhz_clk -source [get_ports clk] -multiply_by 4 -divide_by 5 [get_pins pll_0_inst/clk_out]

##Switches
set_property -dict {PACKAGE_PIN J15 IOSTANDARD LVCMOS33} [get_ports {switches[0]}]
set_property -dict {PACKAGE_PIN L16 IOSTANDARD LVCMOS33} [get_ports {switches[1]}]
set_property -dict {PACKAGE_PIN M13 IOSTANDARD LVCMOS33} [get_ports {switches[2]}]
set_property -dict {PACKAGE_PIN R15 IOSTANDARD LVCMOS33} [get_ports {switches[3]}]
set_property -dict {PACKAGE_PIN R17 IOSTANDARD LVCMOS33} [get_ports {switches[4]}]
set_property -dict {PACKAGE_PIN T18 IOSTANDARD LVCMOS33} [get_ports {switches[5]}]
set_property -dict {PACKAGE_PIN U18 IOSTANDARD LVCMOS33} [get_ports {switches[6]}]
set_property -dict {PACKAGE_PIN R13 IOSTANDARD LVCMOS33} [get_ports {switches[7]}]
set_property -dict {PACKAGE_PIN T8 IOSTANDARD LVCMOS18} [get_ports {switches[8]}]
set_property -dict {PACKAGE_PIN U8 IOSTANDARD LVCMOS18} [get_ports {switches[9]}]
set_property -dict {PACKAGE_PIN R16 IOSTANDARD LVCMOS33} [get_ports {switches[10]}]
set_property -dict {PACKAGE_PIN T13 IOSTANDARD LVCMOS33} [get_ports {switches[11]}]
set_property -dict {PACKAGE_PIN H6 IOSTANDARD LVCMOS33} [get_ports {switches[12]}]
set_property -dict {PACKAGE_PIN U12 IOSTANDARD LVCMOS33} [get_ports {switches[13]}]
set_property -dict {PACKAGE_PIN U11 IOSTANDARD LVCMOS33} [get_ports {switches[14]}]
set_property -dict {PACKAGE_PIN V10 IOSTANDARD LVCMOS33} [get_ports {switches[15]}]

## LEDs
set_property -dict {PACKAGE_PIN H17 IOSTANDARD LVCMOS33} [get_ports {green_leds[0]}]
set_property -dict {PACKAGE_PIN K15 IOSTANDARD LVCMOS33} [get_ports {green_leds[1]}]
set_property -dict {PACKAGE_PIN J13 IOSTANDARD LVCMOS33} [get_ports {green_leds[2]}]
set_property -dict {PACKAGE_PIN N14 IOSTANDARD LVCMOS33} [get_ports {green_leds[3]}]
set_property -dict {PACKAGE_PIN R18 IOSTANDARD LVCMOS33} [get_ports {green_leds[4]}]
set_property -dict {PACKAGE_PIN V17 IOSTANDARD LVCMOS33} [get_ports {green_leds[5]}]
set_property -dict {PACKAGE_PIN U17 IOSTANDARD LVCMOS33} [get_ports {green_leds[6]}]
set_property -dict {PACKAGE_PIN U16 IOSTANDARD LVCMOS33} [get_ports {green_leds[7]}]
set_property -dict {PACKAGE_PIN V16 IOSTANDARD LVCMOS33} [get_ports {green_leds[8]}]
set_property -dict {PACKAGE_PIN T15 IOSTANDARD LVCMOS33} [get_ports {green_leds[9]}]
set_property -dict {PACKAGE_PIN U14 IOSTANDARD LVCMOS33} [get_ports {green_leds[10]}]
set_property -dict {PACKAGE_PIN T16 IOSTANDARD LVCMOS33} [get_ports {green_leds[11]}]
set_property -dict {PACKAGE_PIN V15 IOSTANDARD LVCMOS33} [get_ports {green_leds[12]}]
set_property -dict {PACKAGE_PIN V14 IOSTANDARD LVCMOS33} [get_ports {green_leds[13]}]
set_property -dict {PACKAGE_PIN V12 IOSTANDARD LVCMOS33} [get_ports {green_leds[14]}]
set_property -dict {PACKAGE_PIN V11 IOSTANDARD LVCMOS33} [get_ports {green_leds[15]}]

set_property -dict {PACKAGE_PIN R12 IOSTANDARD LVCMOS33} [get_ports {rgb_leds[0]}]
set_property -dict {PACKAGE_PIN M16 IOSTANDARD LVCMOS33} [get_ports {rgb_leds[1]}]
set_property -dict {PACKAGE_PIN N15 IOSTANDARD LVCMOS33} [get_ports {rgb_leds[2]}]
set_property -dict {PACKAGE_PIN G14 IOSTANDARD LVCMOS33} [get_ports {rgb_leds[3]}]
set_property -dict {PACKAGE_PIN R11 IOSTANDARD LVCMOS33} [get_ports {rgb_leds[4]}]
set_property -dict {PACKAGE_PIN N16 IOSTANDARD LVCMOS33} [get_ports {rgb_leds[5]}]

##7 segment display
set_property -dict {PACKAGE_PIN T10 IOSTANDARD LVCMOS33} [get_ports {seven_segments[0]}]
set_property -dict {PACKAGE_PIN R10 IOSTANDARD LVCMOS33} [get_ports {seven_segments[1]}]
set_property -dict {PACKAGE_PIN K16 IOSTANDARD LVCMOS33} [get_ports {seven_segments[2]}]
set_property -dict {PACKAGE_PIN K13 IOSTANDARD LVCMOS33} [get_ports {seven_segments[3]}]
set_property -dict {PACKAGE_PIN P15 IOSTANDARD LVCMOS33} [get_ports {seven_segments[4]}]
set_property -dict {PACKAGE_PIN T11 IOSTANDARD LVCMOS33} [get_ports {seven_segments[5]}]
set_property -dict {PACKAGE_PIN L18 IOSTANDARD LVCMOS33} [get_ports {seven_segments[6]}]

set_property -dict {PACKAGE_PIN H15 IOSTANDARD LVCMOS33} [get_ports {seven_segments[7]}]

set_property -dict {PACKAGE_PIN J17 IOSTANDARD LVCMOS33} [get_ports {seven_segments_drive[0]}]
set_property -dict {PACKAGE_PIN J18 IOSTANDARD LVCMOS33} [get_ports {seven_segments_drive[1]}]
set_property -dict {PACKAGE_PIN T9 IOSTANDARD LVCMOS33} [get_ports {seven_segments_drive[2]}]
set_property -dict {PACKAGE_PIN J14 IOSTANDARD LVCMOS33} [get_ports {seven_segments_drive[3]}]
set_property -dict {PACKAGE_PIN P14 IOSTANDARD LVCMOS33} [get_ports {seven_segments_drive[4]}]
set_property -dict {PACKAGE_PIN T14 IOSTANDARD LVCMOS33} [get_ports {seven_segments_drive[5]}]
set_property -dict {PACKAGE_PIN K2 IOSTANDARD LVCMOS33} [get_ports {seven_segments_drive[6]}]
set_property -dict {PACKAGE_PIN U13 IOSTANDARD LVCMOS33} [get_ports {seven_segments_drive[7]}]

##Buttons
set_property -dict {PACKAGE_PIN C12 IOSTANDARD LVCMOS33} [get_ports cpu_reset_btn]

set_property -dict {PACKAGE_PIN N17 IOSTANDARD LVCMOS33} [get_ports {buttons[0]}]
set_property -dict {PACKAGE_PIN M18 IOSTANDARD LVCMOS33} [get_ports {buttons[4]}]
set_property -dict {PACKAGE_PIN P17 IOSTANDARD LVCMOS33} [get_ports {buttons[1]}]
set_property -dict {PACKAGE_PIN M17 IOSTANDARD LVCMOS33} [get_ports {buttons[3]}]
set_property -dict {PACKAGE_PIN P18 IOSTANDARD LVCMOS33} [get_ports {buttons[2]}]


##Pmod Headers


##Pmod Header JA

#set_property -dict { PACKAGE_PIN C17   IOSTANDARD LVCMOS33 } [get_ports { JA[1] }]; #IO_L20N_T3_A19_15 Sch=ja[1]
#set_property -dict { PACKAGE_PIN D18   IOSTANDARD LVCMOS33 } [get_ports { JA[2] }]; #IO_L21N_T3_DQS_A18_15 Sch=ja[2]
#set_property -dict { PACKAGE_PIN E18   IOSTANDARD LVCMOS33 } [get_ports { JA[3] }]; #IO_L21P_T3_DQS_15 Sch=ja[3]
#set_property -dict { PACKAGE_PIN G17   IOSTANDARD LVCMOS33 } [get_ports { JA[4] }]; #IO_L18N_T2_A23_15 Sch=ja[4]
#set_property -dict { PACKAGE_PIN D17   IOSTANDARD LVCMOS33 } [get_ports { JA[7] }]; #IO_L16N_T2_A27_15 Sch=ja[7]
#set_property -dict { PACKAGE_PIN E17   IOSTANDARD LVCMOS33 } [get_ports { JA[8] }]; #IO_L16P_T2_A28_15 Sch=ja[8]
#set_property -dict { PACKAGE_PIN F18   IOSTANDARD LVCMOS33 } [get_ports { JA[9] }]; #IO_L22N_T3_A16_15 Sch=ja[9]
#set_property -dict { PACKAGE_PIN G18   IOSTANDARD LVCMOS33 } [get_ports { JA[10] }]; #IO_L22P_T3_A17_15 Sch=ja[10]


##Pmod Header JB

#set_property -dict { PACKAGE_PIN D14   IOSTANDARD LVCMOS33 } [get_ports { JB[1] }]; #IO_L1P_T0_AD0P_15 Sch=jb[1]
#set_property -dict { PACKAGE_PIN F16   IOSTANDARD LVCMOS33 } [get_ports { JB[2] }]; #IO_L14N_T2_SRCC_15 Sch=jb[2]
#set_property -dict { PACKAGE_PIN G16   IOSTANDARD LVCMOS33 } [get_ports { JB[3] }]; #IO_L13N_T2_MRCC_15 Sch=jb[3]
#set_property -dict { PACKAGE_PIN H14   IOSTANDARD LVCMOS33 } [get_ports { JB[4] }]; #IO_L15P_T2_DQS_15 Sch=jb[4]
#set_property -dict { PACKAGE_PIN E16   IOSTANDARD LVCMOS33 } [get_ports { JB[7] }]; #IO_L11N_T1_SRCC_15 Sch=jb[7]
#set_property -dict { PACKAGE_PIN F13   IOSTANDARD LVCMOS33 } [get_ports { JB[8] }]; #IO_L5P_T0_AD9P_15 Sch=jb[8]
#set_property -dict { PACKAGE_PIN G13   IOSTANDARD LVCMOS33 } [get_ports { JB[9] }]; #IO_0_15 Sch=jb[9]
#set_property -dict { PACKAGE_PIN H16   IOSTANDARD LVCMOS33 } [get_ports { JB[10] }]; #IO_L13P_T2_MRCC_15 Sch=jb[10]


##Pmod Header JC

#set_property -dict { PACKAGE_PIN K1    IOSTANDARD LVCMOS33 } [get_ports { JC[1] }]; #IO_L23N_T3_35 Sch=jc[1]
#set_property -dict { PACKAGE_PIN F6    IOSTANDARD LVCMOS33 } [get_ports { JC[2] }]; #IO_L19N_T3_VREF_35 Sch=jc[2]
#set_property -dict { PACKAGE_PIN J2    IOSTANDARD LVCMOS33 } [get_ports { JC[3] }]; #IO_L22N_T3_35 Sch=jc[3]
#set_property -dict { PACKAGE_PIN G6    IOSTANDARD LVCMOS33 } [get_ports { JC[4] }]; #IO_L19P_T3_35 Sch=jc[4]
#set_property -dict { PACKAGE_PIN E7    IOSTANDARD LVCMOS33 } [get_ports { JC[7] }]; #IO_L6P_T0_35 Sch=jc[7]
#set_property -dict { PACKAGE_PIN J3    IOSTANDARD LVCMOS33 } [get_ports { JC[8] }]; #IO_L22P_T3_35 Sch=jc[8]
#set_property -dict { PACKAGE_PIN J4    IOSTANDARD LVCMOS33 } [get_ports { JC[9] }]; #IO_L21P_T3_DQS_35 Sch=jc[9]
#set_property -dict { PACKAGE_PIN E6    IOSTANDARD LVCMOS33 } [get_ports { JC[10] }]; #IO_L5P_T0_AD13P_35 Sch=jc[10]


##Pmod Header JD

#set_property -dict { PACKAGE_PIN H4    IOSTANDARD LVCMOS33 } [get_ports { JD[1] }]; #IO_L21N_T3_DQS_35 Sch=jd[1]
#set_property -dict { PACKAGE_PIN H1    IOSTANDARD LVCMOS33 } [get_ports { JD[2] }]; #IO_L17P_T2_35 Sch=jd[2]
#set_property -dict { PACKAGE_PIN G1    IOSTANDARD LVCMOS33 } [get_ports { JD[3] }]; #IO_L17N_T2_35 Sch=jd[3]
#set_property -dict { PACKAGE_PIN G3    IOSTANDARD LVCMOS33 } [get_ports { JD[4] }]; #IO_L20N_T3_35 Sch=jd[4]
#set_property -dict { PACKAGE_PIN H2    IOSTANDARD LVCMOS33 } [get_ports { JD[7] }]; #IO_L15P_T2_DQS_35 Sch=jd[7]
#set_property -dict { PACKAGE_PIN G4    IOSTANDARD LVCMOS33 } [get_ports { JD[8] }]; #IO_L20P_T3_35 Sch=jd[8]
#set_property -dict { PACKAGE_PIN G2    IOSTANDARD LVCMOS33 } [get_ports { JD[9] }]; #IO_L15N_T2_DQS_35 Sch=jd[9]
#set_property -dict { PACKAGE_PIN F3    IOSTANDARD LVCMOS33 } [get_ports { JD[10] }]; #IO_L13N_T2_MRCC_35 Sch=jd[10]


##Pmod Header JXADC

#set_property -dict { PACKAGE_PIN A14   IOSTANDARD LVDS     } [get_ports { XA_N[1] }]; #IO_L9N_T1_DQS_AD3N_15 Sch=xa_n[1]
#set_property -dict { PACKAGE_PIN A13   IOSTANDARD LVDS     } [get_ports { XA_P[1] }]; #IO_L9P_T1_DQS_AD3P_15 Sch=xa_p[1]
#set_property -dict { PACKAGE_PIN A16   IOSTANDARD LVDS     } [get_ports { XA_N[2] }]; #IO_L8N_T1_AD10N_15 Sch=xa_n[2]
#set_property -dict { PACKAGE_PIN A15   IOSTANDARD LVDS     } [get_ports { XA_P[2] }]; #IO_L8P_T1_AD10P_15 Sch=xa_p[2]
#set_property -dict { PACKAGE_PIN B17   IOSTANDARD LVDS     } [get_ports { XA_N[3] }]; #IO_L7N_T1_AD2N_15 Sch=xa_n[3]
#set_property -dict { PACKAGE_PIN B16   IOSTANDARD LVDS     } [get_ports { XA_P[3] }]; #IO_L7P_T1_AD2P_15 Sch=xa_p[3]
#set_property -dict { PACKAGE_PIN A18   IOSTANDARD LVDS     } [get_ports { XA_N[4] }]; #IO_L10N_T1_AD11N_15 Sch=xa_n[4]
#set_property -dict { PACKAGE_PIN B18   IOSTANDARD LVDS     } [get_ports { XA_P[4] }]; #IO_L10P_T1_AD11P_15 Sch=xa_p[4]


##VGA Connector

#set_property -dict { PACKAGE_PIN A3    IOSTANDARD LVCMOS33 } [get_ports { VGA_R[0] }]; #IO_L8N_T1_AD14N_35 Sch=vga_r[0]
#set_property -dict { PACKAGE_PIN B4    IOSTANDARD LVCMOS33 } [get_ports { VGA_R[1] }]; #IO_L7N_T1_AD6N_35 Sch=vga_r[1]
#set_property -dict { PACKAGE_PIN C5    IOSTANDARD LVCMOS33 } [get_ports { VGA_R[2] }]; #IO_L1N_T0_AD4N_35 Sch=vga_r[2]
#set_property -dict { PACKAGE_PIN A4    IOSTANDARD LVCMOS33 } [get_ports { VGA_R[3] }]; #IO_L8P_T1_AD14P_35 Sch=vga_r[3]

#set_property -dict { PACKAGE_PIN C6    IOSTANDARD LVCMOS33 } [get_ports { VGA_G[0] }]; #IO_L1P_T0_AD4P_35 Sch=vga_g[0]
#set_property -dict { PACKAGE_PIN A5    IOSTANDARD LVCMOS33 } [get_ports { VGA_G[1] }]; #IO_L3N_T0_DQS_AD5N_35 Sch=vga_g[1]
#set_property -dict { PACKAGE_PIN B6    IOSTANDARD LVCMOS33 } [get_ports { VGA_G[2] }]; #IO_L2N_T0_AD12N_35 Sch=vga_g[2]
#set_property -dict { PACKAGE_PIN A6    IOSTANDARD LVCMOS33 } [get_ports { VGA_G[3] }]; #IO_L3P_T0_DQS_AD5P_35 Sch=vga_g[3]

#set_property -dict { PACKAGE_PIN B7    IOSTANDARD LVCMOS33 } [get_ports { VGA_B[0] }]; #IO_L2P_T0_AD12P_35 Sch=vga_b[0]
#set_property -dict { PACKAGE_PIN C7    IOSTANDARD LVCMOS33 } [get_ports { VGA_B[1] }]; #IO_L4N_T0_35 Sch=vga_b[1]
#set_property -dict { PACKAGE_PIN D7    IOSTANDARD LVCMOS33 } [get_ports { VGA_B[2] }]; #IO_L6N_T0_VREF_35 Sch=vga_b[2]
#set_property -dict { PACKAGE_PIN D8    IOSTANDARD LVCMOS33 } [get_ports { VGA_B[3] }]; #IO_L4P_T0_35 Sch=vga_b[3]

#set_property -dict { PACKAGE_PIN B11   IOSTANDARD LVCMOS33 } [get_ports { VGA_HS }]; #IO_L4P_T0_15 Sch=vga_hs
#set_property -dict { PACKAGE_PIN B12   IOSTANDARD LVCMOS33 } [get_ports { VGA_VS }]; #IO_L3N_T0_DQS_AD1N_15 Sch=vga_vs


##Micro SD Connector

#set_property -dict { PACKAGE_PIN E2    IOSTANDARD LVCMOS33 } [get_ports { SD_RESET }]; #IO_L14P_T2_SRCC_35 Sch=sd_reset
#set_property -dict { PACKAGE_PIN A1    IOSTANDARD LVCMOS33 } [get_ports { SD_CD }]; #IO_L9N_T1_DQS_AD7N_35 Sch=sd_cd
#set_property -dict { PACKAGE_PIN B1    IOSTANDARD LVCMOS33 } [get_ports { SD_SCK }]; #IO_L9P_T1_DQS_AD7P_35 Sch=sd_sck
#set_property -dict { PACKAGE_PIN C1    IOSTANDARD LVCMOS33 } [get_ports { SD_CMD }]; #IO_L16N_T2_35 Sch=sd_cmd
#set_property -dict { PACKAGE_PIN C2    IOSTANDARD LVCMOS33 } [get_ports { SD_DAT[0] }]; #IO_L16P_T2_35 Sch=sd_dat[0]
#set_property -dict { PACKAGE_PIN E1    IOSTANDARD LVCMOS33 } [get_ports { SD_DAT[1] }]; #IO_L18N_T2_35 Sch=sd_dat[1]
#set_property -dict { PACKAGE_PIN F1    IOSTANDARD LVCMOS33 } [get_ports { SD_DAT[2] }]; #IO_L18P_T2_35 Sch=sd_dat[2]
#set_property -dict { PACKAGE_PIN D2    IOSTANDARD LVCMOS33 } [get_ports { SD_DAT[3] }]; #IO_L14N_T2_SRCC_35 Sch=sd_dat[3]


##Accelerometer

#set_property -dict { PACKAGE_PIN E15   IOSTANDARD LVCMOS33 } [get_ports { ACL_MISO }]; #IO_L11P_T1_SRCC_15 Sch=acl_miso
#set_property -dict { PACKAGE_PIN F14   IOSTANDARD LVCMOS33 } [get_ports { ACL_MOSI }]; #IO_L5N_T0_AD9N_15 Sch=acl_mosi
#set_property -dict { PACKAGE_PIN F15   IOSTANDARD LVCMOS33 } [get_ports { ACL_SCLK }]; #IO_L14P_T2_SRCC_15 Sch=acl_sclk
#set_property -dict { PACKAGE_PIN D15   IOSTANDARD LVCMOS33 } [get_ports { ACL_CSN }]; #IO_L12P_T1_MRCC_15 Sch=acl_csn
#set_property -dict { PACKAGE_PIN B13   IOSTANDARD LVCMOS33 } [get_ports { ACL_INT[1] }]; #IO_L2P_T0_AD8P_15 Sch=acl_int[1]
#set_property -dict { PACKAGE_PIN C16   IOSTANDARD LVCMOS33 } [get_ports { ACL_INT[2] }]; #IO_L20P_T3_A20_15 Sch=acl_int[2]


##Temperature Sensor

#set_property -dict { PACKAGE_PIN C14   IOSTANDARD LVCMOS33 } [get_ports { TMP_SCL }]; #IO_L1N_T0_AD0N_15 Sch=tmp_scl
#set_property -dict { PACKAGE_PIN C15   IOSTANDARD LVCMOS33 } [get_ports { TMP_SDA }]; #IO_L12N_T1_MRCC_15 Sch=tmp_sda
#set_property -dict { PACKAGE_PIN D13   IOSTANDARD LVCMOS33 } [get_ports { TMP_INT }]; #IO_L6N_T0_VREF_15 Sch=tmp_int
#set_property -dict { PACKAGE_PIN B14   IOSTANDARD LVCMOS33 } [get_ports { TMP_CT }]; #IO_L2N_T0_AD8N_15 Sch=tmp_ct

##Omnidirectional Microphone

#set_property -dict { PACKAGE_PIN J5    IOSTANDARD LVCMOS33 } [get_ports { M_CLK }]; #IO_25_35 Sch=m_clk
#set_property -dict { PACKAGE_PIN H5    IOSTANDARD LVCMOS33 } [get_ports { M_DATA }]; #IO_L24N_T3_35 Sch=m_data
#set_property -dict { PACKAGE_PIN F5    IOSTANDARD LVCMOS33 } [get_ports { M_LRSEL }]; #IO_0_35 Sch=m_lrsel


##PWM Audio Amplifier

#set_property -dict { PACKAGE_PIN A11   IOSTANDARD LVCMOS33 } [get_ports { AUD_PWM }]; #IO_L4N_T0_15 Sch=aud_pwm
#set_property -dict { PACKAGE_PIN D12   IOSTANDARD LVCMOS33 } [get_ports { AUD_SD }]; #IO_L6P_T0_15 Sch=aud_sd


##USB-RS232 Interface

set_property -dict {PACKAGE_PIN C4 IOSTANDARD LVCMOS33} [get_ports uart_txd]
set_property -dict {PACKAGE_PIN D4 IOSTANDARD LVCMOS33} [get_ports uart_rxd]
#set_property -dict { PACKAGE_PIN D3    IOSTANDARD LVCMOS33 } [get_ports { UART_CTS }]; #IO_L12N_T1_MRCC_35 Sch=uart_cts
#set_property -dict { PACKAGE_PIN E5    IOSTANDARD LVCMOS33 } [get_ports { UART_RTS }]; #IO_L5N_T0_AD13N_35 Sch=uart_rts

##USB HID (PS/2)

#set_property -dict { PACKAGE_PIN F4    IOSTANDARD LVCMOS33 } [get_ports { PS2_CLK }]; #IO_L13P_T2_MRCC_35 Sch=ps2_clk
#set_property -dict { PACKAGE_PIN B2    IOSTANDARD LVCMOS33 } [get_ports { PS2_DATA }]; #IO_L10N_T1_AD15N_35 Sch=ps2_data


##SMSC Ethernet PHY

#set_property -dict { PACKAGE_PIN C9    IOSTANDARD LVCMOS33 } [get_ports { ETH_MDC }]; #IO_L11P_T1_SRCC_16 Sch=eth_mdc
#set_property -dict { PACKAGE_PIN A9    IOSTANDARD LVCMOS33 } [get_ports { ETH_MDIO }]; #IO_L14N_T2_SRCC_16 Sch=eth_mdio
#set_property -dict { PACKAGE_PIN B3    IOSTANDARD LVCMOS33 } [get_ports { ETH_RSTN }]; #IO_L10P_T1_AD15P_35 Sch=eth_rstn
#set_property -dict { PACKAGE_PIN D9    IOSTANDARD LVCMOS33 } [get_ports { ETH_CRSDV }]; #IO_L6N_T0_VREF_16 Sch=eth_crsdv
#set_property -dict { PACKAGE_PIN C10   IOSTANDARD LVCMOS33 } [get_ports { ETH_RXERR }]; #IO_L13N_T2_MRCC_16 Sch=eth_rxerr
#set_property -dict { PACKAGE_PIN C11   IOSTANDARD LVCMOS33 } [get_ports { ETH_RXD[0] }]; #IO_L13P_T2_MRCC_16 Sch=eth_rxd[0]
#set_property -dict { PACKAGE_PIN D10   IOSTANDARD LVCMOS33 } [get_ports { ETH_RXD[1] }]; #IO_L19N_T3_VREF_16 Sch=eth_rxd[1]
#set_property -dict { PACKAGE_PIN B9    IOSTANDARD LVCMOS33 } [get_ports { ETH_TXEN }]; #IO_L11N_T1_SRCC_16 Sch=eth_txen
#set_property -dict { PACKAGE_PIN A10   IOSTANDARD LVCMOS33 } [get_ports { ETH_TXD[0] }]; #IO_L14P_T2_SRCC_16 Sch=eth_txd[0]
#set_property -dict { PACKAGE_PIN A8    IOSTANDARD LVCMOS33 } [get_ports { ETH_TXD[1] }]; #IO_L12N_T1_MRCC_16 Sch=eth_txd[1]
#set_property -dict { PACKAGE_PIN D5    IOSTANDARD LVCMOS33 } [get_ports { ETH_REFCLK }]; #IO_L11P_T1_SRCC_35 Sch=eth_refclk
#set_property -dict { PACKAGE_PIN B8    IOSTANDARD LVCMOS33 } [get_ports { ETH_INTN }]; #IO_L12P_T1_MRCC_16 Sch=eth_intn


##Quad SPI Flash

#set_property -dict { PACKAGE_PIN K17   IOSTANDARD LVCMOS33 } [get_ports { QSPI_DQ[0] }]; #IO_L1P_T0_D00_MOSI_14 Sch=qspi_dq[0]
#set_property -dict { PACKAGE_PIN K18   IOSTANDARD LVCMOS33 } [get_ports { QSPI_DQ[1] }]; #IO_L1N_T0_D01_DIN_14 Sch=qspi_dq[1]
#set_property -dict { PACKAGE_PIN L14   IOSTANDARD LVCMOS33 } [get_ports { QSPI_DQ[2] }]; #IO_L2P_T0_D02_14 Sch=qspi_dq[2]
#set_property -dict { PACKAGE_PIN M14   IOSTANDARD LVCMOS33 } [get_ports { QSPI_DQ[3] }]; #IO_L2N_T0_D03_14 Sch=qspi_dq[3]
#set_property -dict { PACKAGE_PIN L13   IOSTANDARD LVCMOS33 } [get_ports { QSPI_CSN }]; #IO_L6P_T0_FCS_B_14 Sch=qspi_csn


create_debug_core u_ila_0 ila
set_property ALL_PROBE_SAME_MU true [get_debug_cores u_ila_0]
set_property ALL_PROBE_SAME_MU_CNT 1 [get_debug_cores u_ila_0]
set_property C_ADV_TRIGGER false [get_debug_cores u_ila_0]
set_property C_DATA_DEPTH 4096 [get_debug_cores u_ila_0]
set_property C_EN_STRG_QUAL false [get_debug_cores u_ila_0]
set_property C_INPUT_PIPE_STAGES 0 [get_debug_cores u_ila_0]
set_property C_TRIGIN_EN false [get_debug_cores u_ila_0]
set_property C_TRIGOUT_EN false [get_debug_cores u_ila_0]
set_property port_width 1 [get_debug_ports u_ila_0/clk]
connect_debug_port u_ila_0/clk [get_nets [list ddr2_ctrl_inst_0/u_ddr2_ctrl_mig/u_ddr2_infrastructure/CLK]]
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe0]
set_property port_width 32 [get_debug_ports u_ila_0/probe0]
connect_debug_port u_ila_0/probe0 [get_nets [list {hwACtrlExt_par2[0]} {hwACtrlExt_par2[1]} {hwACtrlExt_par2[2]} {hwACtrlExt_par2[3]} {hwACtrlExt_par2[4]} {hwACtrlExt_par2[5]} {hwACtrlExt_par2[6]} {hwACtrlExt_par2[7]} {hwACtrlExt_par2[8]} {hwACtrlExt_par2[9]} {hwACtrlExt_par2[10]} {hwACtrlExt_par2[11]} {hwACtrlExt_par2[12]} {hwACtrlExt_par2[13]} {hwACtrlExt_par2[14]} {hwACtrlExt_par2[15]} {hwACtrlExt_par2[16]} {hwACtrlExt_par2[17]} {hwACtrlExt_par2[18]} {hwACtrlExt_par2[19]} {hwACtrlExt_par2[20]} {hwACtrlExt_par2[21]} {hwACtrlExt_par2[22]} {hwACtrlExt_par2[23]} {hwACtrlExt_par2[24]} {hwACtrlExt_par2[25]} {hwACtrlExt_par2[26]} {hwACtrlExt_par2[27]} {hwACtrlExt_par2[28]} {hwACtrlExt_par2[29]} {hwACtrlExt_par2[30]} {hwACtrlExt_par2[31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe1]
set_property port_width 32 [get_debug_ports u_ila_0/probe1]
connect_debug_port u_ila_0/probe1 [get_nets [list {hwACtrlExt_par1[0]} {hwACtrlExt_par1[1]} {hwACtrlExt_par1[2]} {hwACtrlExt_par1[3]} {hwACtrlExt_par1[4]} {hwACtrlExt_par1[5]} {hwACtrlExt_par1[6]} {hwACtrlExt_par1[7]} {hwACtrlExt_par1[8]} {hwACtrlExt_par1[9]} {hwACtrlExt_par1[10]} {hwACtrlExt_par1[11]} {hwACtrlExt_par1[12]} {hwACtrlExt_par1[13]} {hwACtrlExt_par1[14]} {hwACtrlExt_par1[15]} {hwACtrlExt_par1[16]} {hwACtrlExt_par1[17]} {hwACtrlExt_par1[18]} {hwACtrlExt_par1[19]} {hwACtrlExt_par1[20]} {hwACtrlExt_par1[21]} {hwACtrlExt_par1[22]} {hwACtrlExt_par1[23]} {hwACtrlExt_par1[24]} {hwACtrlExt_par1[25]} {hwACtrlExt_par1[26]} {hwACtrlExt_par1[27]} {hwACtrlExt_par1[28]} {hwACtrlExt_par1[29]} {hwACtrlExt_par1[30]} {hwACtrlExt_par1[31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe2]
set_property port_width 32 [get_debug_ports u_ila_0/probe2]
connect_debug_port u_ila_0/probe2 [get_nets [list {bram_s_i[2][dout][0]} {bram_s_i[2][dout][1]} {bram_s_i[2][dout][2]} {bram_s_i[2][dout][3]} {bram_s_i[2][dout][4]} {bram_s_i[2][dout][5]} {bram_s_i[2][dout][6]} {bram_s_i[2][dout][7]} {bram_s_i[2][dout][8]} {bram_s_i[2][dout][9]} {bram_s_i[2][dout][10]} {bram_s_i[2][dout][11]} {bram_s_i[2][dout][12]} {bram_s_i[2][dout][13]} {bram_s_i[2][dout][14]} {bram_s_i[2][dout][15]} {bram_s_i[2][dout][16]} {bram_s_i[2][dout][17]} {bram_s_i[2][dout][18]} {bram_s_i[2][dout][19]} {bram_s_i[2][dout][20]} {bram_s_i[2][dout][21]} {bram_s_i[2][dout][22]} {bram_s_i[2][dout][23]} {bram_s_i[2][dout][24]} {bram_s_i[2][dout][25]} {bram_s_i[2][dout][26]} {bram_s_i[2][dout][27]} {bram_s_i[2][dout][28]} {bram_s_i[2][dout][29]} {bram_s_i[2][dout][30]} {bram_s_i[2][dout][31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe3]
set_property port_width 32 [get_debug_ports u_ila_0/probe3]
connect_debug_port u_ila_0/probe3 [get_nets [list {bram_s_i[1][dout][0]} {bram_s_i[1][dout][1]} {bram_s_i[1][dout][2]} {bram_s_i[1][dout][3]} {bram_s_i[1][dout][4]} {bram_s_i[1][dout][5]} {bram_s_i[1][dout][6]} {bram_s_i[1][dout][7]} {bram_s_i[1][dout][8]} {bram_s_i[1][dout][9]} {bram_s_i[1][dout][10]} {bram_s_i[1][dout][11]} {bram_s_i[1][dout][12]} {bram_s_i[1][dout][13]} {bram_s_i[1][dout][14]} {bram_s_i[1][dout][15]} {bram_s_i[1][dout][16]} {bram_s_i[1][dout][17]} {bram_s_i[1][dout][18]} {bram_s_i[1][dout][19]} {bram_s_i[1][dout][20]} {bram_s_i[1][dout][21]} {bram_s_i[1][dout][22]} {bram_s_i[1][dout][23]} {bram_s_i[1][dout][24]} {bram_s_i[1][dout][25]} {bram_s_i[1][dout][26]} {bram_s_i[1][dout][27]} {bram_s_i[1][dout][28]} {bram_s_i[1][dout][29]} {bram_s_i[1][dout][30]} {bram_s_i[1][dout][31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe4]
set_property port_width 32 [get_debug_ports u_ila_0/probe4]
connect_debug_port u_ila_0/probe4 [get_nets [list {bram_s_i[0][dout][0]} {bram_s_i[0][dout][1]} {bram_s_i[0][dout][2]} {bram_s_i[0][dout][3]} {bram_s_i[0][dout][4]} {bram_s_i[0][dout][5]} {bram_s_i[0][dout][6]} {bram_s_i[0][dout][7]} {bram_s_i[0][dout][8]} {bram_s_i[0][dout][9]} {bram_s_i[0][dout][10]} {bram_s_i[0][dout][11]} {bram_s_i[0][dout][12]} {bram_s_i[0][dout][13]} {bram_s_i[0][dout][14]} {bram_s_i[0][dout][15]} {bram_s_i[0][dout][16]} {bram_s_i[0][dout][17]} {bram_s_i[0][dout][18]} {bram_s_i[0][dout][19]} {bram_s_i[0][dout][20]} {bram_s_i[0][dout][21]} {bram_s_i[0][dout][22]} {bram_s_i[0][dout][23]} {bram_s_i[0][dout][24]} {bram_s_i[0][dout][25]} {bram_s_i[0][dout][26]} {bram_s_i[0][dout][27]} {bram_s_i[0][dout][28]} {bram_s_i[0][dout][29]} {bram_s_i[0][dout][30]} {bram_s_i[0][dout][31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe5]
set_property port_width 4 [get_debug_ports u_ila_0/probe5]
connect_debug_port u_ila_0/probe5 [get_nets [list {bram_m_i[2][wr][0]} {bram_m_i[2][wr][1]} {bram_m_i[2][wr][2]} {bram_m_i[2][wr][3]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe6]
set_property port_width 32 [get_debug_ports u_ila_0/probe6]
connect_debug_port u_ila_0/probe6 [get_nets [list {bram_m_i[2][din][0]} {bram_m_i[2][din][1]} {bram_m_i[2][din][2]} {bram_m_i[2][din][3]} {bram_m_i[2][din][4]} {bram_m_i[2][din][5]} {bram_m_i[2][din][6]} {bram_m_i[2][din][7]} {bram_m_i[2][din][8]} {bram_m_i[2][din][9]} {bram_m_i[2][din][10]} {bram_m_i[2][din][11]} {bram_m_i[2][din][12]} {bram_m_i[2][din][13]} {bram_m_i[2][din][14]} {bram_m_i[2][din][15]} {bram_m_i[2][din][16]} {bram_m_i[2][din][17]} {bram_m_i[2][din][18]} {bram_m_i[2][din][19]} {bram_m_i[2][din][20]} {bram_m_i[2][din][21]} {bram_m_i[2][din][22]} {bram_m_i[2][din][23]} {bram_m_i[2][din][24]} {bram_m_i[2][din][25]} {bram_m_i[2][din][26]} {bram_m_i[2][din][27]} {bram_m_i[2][din][28]} {bram_m_i[2][din][29]} {bram_m_i[2][din][30]} {bram_m_i[2][din][31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe7]
set_property port_width 13 [get_debug_ports u_ila_0/probe7]
connect_debug_port u_ila_0/probe7 [get_nets [list {bram_m_i[2][addr][0]} {bram_m_i[2][addr][1]} {bram_m_i[2][addr][2]} {bram_m_i[2][addr][3]} {bram_m_i[2][addr][4]} {bram_m_i[2][addr][5]} {bram_m_i[2][addr][6]} {bram_m_i[2][addr][7]} {bram_m_i[2][addr][8]} {bram_m_i[2][addr][9]} {bram_m_i[2][addr][10]} {bram_m_i[2][addr][11]} {bram_m_i[2][addr][12]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe8]
set_property port_width 4 [get_debug_ports u_ila_0/probe8]
connect_debug_port u_ila_0/probe8 [get_nets [list {bram_m_i[1][wr][0]} {bram_m_i[1][wr][1]} {bram_m_i[1][wr][2]} {bram_m_i[1][wr][3]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe9]
set_property port_width 32 [get_debug_ports u_ila_0/probe9]
connect_debug_port u_ila_0/probe9 [get_nets [list {bram_m_i[1][din][0]} {bram_m_i[1][din][1]} {bram_m_i[1][din][2]} {bram_m_i[1][din][3]} {bram_m_i[1][din][4]} {bram_m_i[1][din][5]} {bram_m_i[1][din][6]} {bram_m_i[1][din][7]} {bram_m_i[1][din][8]} {bram_m_i[1][din][9]} {bram_m_i[1][din][10]} {bram_m_i[1][din][11]} {bram_m_i[1][din][12]} {bram_m_i[1][din][13]} {bram_m_i[1][din][14]} {bram_m_i[1][din][15]} {bram_m_i[1][din][16]} {bram_m_i[1][din][17]} {bram_m_i[1][din][18]} {bram_m_i[1][din][19]} {bram_m_i[1][din][20]} {bram_m_i[1][din][21]} {bram_m_i[1][din][22]} {bram_m_i[1][din][23]} {bram_m_i[1][din][24]} {bram_m_i[1][din][25]} {bram_m_i[1][din][26]} {bram_m_i[1][din][27]} {bram_m_i[1][din][28]} {bram_m_i[1][din][29]} {bram_m_i[1][din][30]} {bram_m_i[1][din][31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe10]
set_property port_width 13 [get_debug_ports u_ila_0/probe10]
connect_debug_port u_ila_0/probe10 [get_nets [list {bram_m_i[1][addr][0]} {bram_m_i[1][addr][1]} {bram_m_i[1][addr][2]} {bram_m_i[1][addr][3]} {bram_m_i[1][addr][4]} {bram_m_i[1][addr][5]} {bram_m_i[1][addr][6]} {bram_m_i[1][addr][7]} {bram_m_i[1][addr][8]} {bram_m_i[1][addr][9]} {bram_m_i[1][addr][10]} {bram_m_i[1][addr][11]} {bram_m_i[1][addr][12]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe11]
set_property port_width 4 [get_debug_ports u_ila_0/probe11]
connect_debug_port u_ila_0/probe11 [get_nets [list {bram_m_i[0][wr][0]} {bram_m_i[0][wr][1]} {bram_m_i[0][wr][2]} {bram_m_i[0][wr][3]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe12]
set_property port_width 32 [get_debug_ports u_ila_0/probe12]
connect_debug_port u_ila_0/probe12 [get_nets [list {bram_m_i[0][din][0]} {bram_m_i[0][din][1]} {bram_m_i[0][din][2]} {bram_m_i[0][din][3]} {bram_m_i[0][din][4]} {bram_m_i[0][din][5]} {bram_m_i[0][din][6]} {bram_m_i[0][din][7]} {bram_m_i[0][din][8]} {bram_m_i[0][din][9]} {bram_m_i[0][din][10]} {bram_m_i[0][din][11]} {bram_m_i[0][din][12]} {bram_m_i[0][din][13]} {bram_m_i[0][din][14]} {bram_m_i[0][din][15]} {bram_m_i[0][din][16]} {bram_m_i[0][din][17]} {bram_m_i[0][din][18]} {bram_m_i[0][din][19]} {bram_m_i[0][din][20]} {bram_m_i[0][din][21]} {bram_m_i[0][din][22]} {bram_m_i[0][din][23]} {bram_m_i[0][din][24]} {bram_m_i[0][din][25]} {bram_m_i[0][din][26]} {bram_m_i[0][din][27]} {bram_m_i[0][din][28]} {bram_m_i[0][din][29]} {bram_m_i[0][din][30]} {bram_m_i[0][din][31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe13]
set_property port_width 13 [get_debug_ports u_ila_0/probe13]
connect_debug_port u_ila_0/probe13 [get_nets [list {bram_m_i[0][addr][0]} {bram_m_i[0][addr][1]} {bram_m_i[0][addr][2]} {bram_m_i[0][addr][3]} {bram_m_i[0][addr][4]} {bram_m_i[0][addr][5]} {bram_m_i[0][addr][6]} {bram_m_i[0][addr][7]} {bram_m_i[0][addr][8]} {bram_m_i[0][addr][9]} {bram_m_i[0][addr][10]} {bram_m_i[0][addr][11]} {bram_m_i[0][addr][12]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe14]
set_property port_width 32 [get_debug_ports u_ila_0/probe14]
connect_debug_port u_ila_0/probe14 [get_nets [list {bRamCtrl_SData[0]} {bRamCtrl_SData[1]} {bRamCtrl_SData[2]} {bRamCtrl_SData[3]} {bRamCtrl_SData[4]} {bRamCtrl_SData[5]} {bRamCtrl_SData[6]} {bRamCtrl_SData[7]} {bRamCtrl_SData[8]} {bRamCtrl_SData[9]} {bRamCtrl_SData[10]} {bRamCtrl_SData[11]} {bRamCtrl_SData[12]} {bRamCtrl_SData[13]} {bRamCtrl_SData[14]} {bRamCtrl_SData[15]} {bRamCtrl_SData[16]} {bRamCtrl_SData[17]} {bRamCtrl_SData[18]} {bRamCtrl_SData[19]} {bRamCtrl_SData[20]} {bRamCtrl_SData[21]} {bRamCtrl_SData[22]} {bRamCtrl_SData[23]} {bRamCtrl_SData[24]} {bRamCtrl_SData[25]} {bRamCtrl_SData[26]} {bRamCtrl_SData[27]} {bRamCtrl_SData[28]} {bRamCtrl_SData[29]} {bRamCtrl_SData[30]} {bRamCtrl_SData[31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe15]
set_property port_width 3 [get_debug_ports u_ila_0/probe15]
connect_debug_port u_ila_0/probe15 [get_nets [list {bRamCtrl_Mcmd[0]} {bRamCtrl_Mcmd[1]} {bRamCtrl_Mcmd[2]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe16]
set_property port_width 32 [get_debug_ports u_ila_0/probe16]
connect_debug_port u_ila_0/probe16 [get_nets [list {bRamCtrl_MData[0]} {bRamCtrl_MData[1]} {bRamCtrl_MData[2]} {bRamCtrl_MData[3]} {bRamCtrl_MData[4]} {bRamCtrl_MData[5]} {bRamCtrl_MData[6]} {bRamCtrl_MData[7]} {bRamCtrl_MData[8]} {bRamCtrl_MData[9]} {bRamCtrl_MData[10]} {bRamCtrl_MData[11]} {bRamCtrl_MData[12]} {bRamCtrl_MData[13]} {bRamCtrl_MData[14]} {bRamCtrl_MData[15]} {bRamCtrl_MData[16]} {bRamCtrl_MData[17]} {bRamCtrl_MData[18]} {bRamCtrl_MData[19]} {bRamCtrl_MData[20]} {bRamCtrl_MData[21]} {bRamCtrl_MData[22]} {bRamCtrl_MData[23]} {bRamCtrl_MData[24]} {bRamCtrl_MData[25]} {bRamCtrl_MData[26]} {bRamCtrl_MData[27]} {bRamCtrl_MData[28]} {bRamCtrl_MData[29]} {bRamCtrl_MData[30]} {bRamCtrl_MData[31]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe17]
set_property port_width 4 [get_debug_ports u_ila_0/probe17]
connect_debug_port u_ila_0/probe17 [get_nets [list {bRamCtrl_MByteEn[0]} {bRamCtrl_MByteEn[1]} {bRamCtrl_MByteEn[2]} {bRamCtrl_MByteEn[3]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe18]
set_property port_width 16 [get_debug_ports u_ila_0/probe18]
connect_debug_port u_ila_0/probe18 [get_nets [list {bRamCtrl_MAddr[0]} {bRamCtrl_MAddr[1]} {bRamCtrl_MAddr[2]} {bRamCtrl_MAddr[3]} {bRamCtrl_MAddr[4]} {bRamCtrl_MAddr[5]} {bRamCtrl_MAddr[6]} {bRamCtrl_MAddr[7]} {bRamCtrl_MAddr[8]} {bRamCtrl_MAddr[9]} {bRamCtrl_MAddr[10]} {bRamCtrl_MAddr[11]} {bRamCtrl_MAddr[12]} {bRamCtrl_MAddr[13]} {bRamCtrl_MAddr[14]} {bRamCtrl_MAddr[15]}]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe19]
set_property port_width 1 [get_debug_ports u_ila_0/probe19]
connect_debug_port u_ila_0/probe19 [get_nets [list hwa_rst]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe20]
set_property port_width 1 [get_debug_ports u_ila_0/probe20]
connect_debug_port u_ila_0/probe20 [get_nets [list hwACtrlExt_ap_done_in]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe21]
set_property port_width 1 [get_debug_ports u_ila_0/probe21]
connect_debug_port u_ila_0/probe21 [get_nets [list hwACtrlExt_ap_idle_in]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe22]
set_property port_width 1 [get_debug_ports u_ila_0/probe22]
connect_debug_port u_ila_0/probe22 [get_nets [list hwACtrlExt_ap_ready_in]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe23]
set_property port_width 1 [get_debug_ports u_ila_0/probe23]
connect_debug_port u_ila_0/probe23 [get_nets [list hwACtrlExt_ap_reset_out]]
create_debug_port u_ila_0 probe
set_property PROBE_TYPE DATA_AND_TRIGGER [get_debug_ports u_ila_0/probe24]
set_property port_width 1 [get_debug_ports u_ila_0/probe24]
connect_debug_port u_ila_0/probe24 [get_nets [list hwACtrlExt_ap_start_out]]
set_property C_CLK_INPUT_FREQ_HZ 300000000 [get_debug_cores dbg_hub]
set_property C_ENABLE_CLK_DIVIDER false [get_debug_cores dbg_hub]
set_property C_USER_SCAN_CHAIN 1 [get_debug_cores dbg_hub]
connect_debug_port dbg_hub/clk [get_nets clk_int]
