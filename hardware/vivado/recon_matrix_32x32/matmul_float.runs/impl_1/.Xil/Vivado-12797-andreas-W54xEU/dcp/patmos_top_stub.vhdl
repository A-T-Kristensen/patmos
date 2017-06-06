-- Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity patmos_top is
  Port ( 
    clk_in : in STD_LOGIC;
    cpu_reset_btn : in STD_LOGIC;
    green_leds : out STD_LOGIC_VECTOR ( 15 downto 0 );
    rgb_leds : out STD_LOGIC_VECTOR ( 5 downto 0 );
    seven_segments : out STD_LOGIC_VECTOR ( 7 downto 0 );
    seven_segments_drive : out STD_LOGIC_VECTOR ( 7 downto 0 );
    buttons : in STD_LOGIC_VECTOR ( 4 downto 0 );
    switches : in STD_LOGIC_VECTOR ( 15 downto 0 );
    uart_txd : in STD_LOGIC;
    uart_rxd : out STD_LOGIC;
    ddr2_dq : inout STD_LOGIC_VECTOR ( 15 downto 0 );
    ddr2_dqs_n : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    ddr2_dqs_p : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    ddr2_addr : out STD_LOGIC_VECTOR ( 12 downto 0 );
    ddr2_ba : out STD_LOGIC_VECTOR ( 2 downto 0 );
    ddr2_ras_n : out STD_LOGIC;
    ddr2_cas_n : out STD_LOGIC;
    ddr2_we_n : out STD_LOGIC;
    ddr2_ck_p : out STD_LOGIC_VECTOR ( 0 to 0 );
    ddr2_ck_n : out STD_LOGIC_VECTOR ( 0 to 0 );
    ddr2_cke : out STD_LOGIC_VECTOR ( 0 to 0 );
    ddr2_cs_n : out STD_LOGIC_VECTOR ( 0 to 0 );
    ddr2_dm : out STD_LOGIC_VECTOR ( 1 downto 0 );
    ddr2_odt : out STD_LOGIC_VECTOR ( 0 to 0 )
  );

end patmos_top;

architecture stub of patmos_top is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
begin
end;
