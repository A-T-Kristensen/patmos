--
-- Copyright: 2013, Technical University of Denmark, DTU Compute
-- Author: Martin Schoeberl (martin@jopdesign.com)
--         Rasmus Bo Soerensen (rasmus@rbscloud.dk)
-- License: Simplified BSD License
--

-- VHDL top level for Patmos in Chisel on Altera de2-115 board
-- used as top level file for simulation of patmos with c program
-- for using a HwA for matrix multiplication with 1 memory 
-- bank.
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity patmos_top is
	port(
		clk 		  	: in  std_logic;
		oLedsPins_led 	: out std_logic_vector(8 downto 0);
		iKeysPins_key 	: in std_logic_vector(3 downto 0);
		oUartPins_txd 	: out std_logic;
		iUartPins_rxd 	: in  std_logic;
        oSRAM_A 	  	: out std_logic_vector(19 downto 0);
        SRAM_DQ 	  	: inout std_logic_vector(15 downto 0);
        oSRAM_CE_N 		: out std_logic;
        oSRAM_OE_N 		: out std_logic;
        oSRAM_WE_N 		: out std_logic;
        oSRAM_LB_N 		: out std_logic;
        oSRAM_UB_N 		: out std_logic
	);
end entity patmos_top;

architecture rtl of patmos_top is

	component Patmos is
		port(
			clk            			: in  std_logic;
			reset    			    : in  std_logic;

			io_comConf_M_Cmd        : out std_logic_vector(2 downto 0);
			io_comConf_M_Addr       : out std_logic_vector(31 downto 0);
			io_comConf_M_Data       : out std_logic_vector(31 downto 0);
			io_comConf_M_ByteEn     : out std_logic_vector(3 downto 0);
			io_comConf_M_RespAccept : out std_logic;
			io_comConf_S_Resp       : in std_logic_vector(1 downto 0);
			io_comConf_S_Data       : in std_logic_vector(31 downto 0);
			io_comConf_S_CmdAccept  : in std_logic;
			io_comConf_S_Reset_n 	: in std_logic;
	      	io_comConf_S_Flag 		: in std_logic_vector(1 downto 0);			

			io_comSpm_M_Cmd         : out std_logic_vector(2 downto 0);
			io_comSpm_M_Addr        : out std_logic_vector(31 downto 0);
			io_comSpm_M_Data        : out std_logic_vector(31 downto 0);
			io_comSpm_M_ByteEn      : out std_logic_vector(3 downto 0);
			io_comSpm_S_Resp        : in std_logic_vector(1 downto 0);
			io_comSpm_S_Data        : in std_logic_vector(31 downto 0);

			io_cpuInfoPins_id   	: in  std_logic_vector(31 downto 0);
			io_cpuInfoPins_cnt  	: in  std_logic_vector(31 downto 0);
			io_ledsPins_led 		: out std_logic_vector(8 downto 0);
			io_keysPins_key 		: in  std_logic_vector(3 downto 0);
			io_uartPins_tx  		: out std_logic;
			io_uartPins_rx  		: in  std_logic;

		    io_sramCtrlPins_ramOut_addr 	: out std_logic_vector(19 downto 0);
		    io_sramCtrlPins_ramOut_doutEna 	: out std_logic;
		    io_sramCtrlPins_ramIn_din 		: in std_logic_vector(15 downto 0);
		    io_sramCtrlPins_ramOut_dout 	: out std_logic_vector(15 downto 0);
		    io_sramCtrlPins_ramOut_nce 		: out std_logic;
		    io_sramCtrlPins_ramOut_noe 		: out std_logic;
		    io_sramCtrlPins_ramOut_nwe 		: out std_logic;
		    io_sramCtrlPins_ramOut_nlb 		: out std_logic;
		    io_sramCtrlPins_ramOut_nub 		: out std_logic;

			io_bRamCtrlPins_MCmd       : out std_logic_vector(2 downto 0);
			io_bRamCtrlPins_MAddr      : out std_logic_vector(15 downto 0);
			io_bRamCtrlPins_MData      : out std_logic_vector(31 downto 0);
			io_bRamCtrlPins_MByteEn    : out std_logic_vector(3 downto 0);
			io_bRamCtrlPins_SData      : in  std_logic_vector(31 downto 0);

			io_hwACtrlPins_ap_start_out : out std_logic;
			io_hwACtrlPins_ap_reset_out : out std_logic;
			io_hwACtrlPins_ap_ready_in 	: in std_logic;
			io_hwACtrlPins_ap_idle_in 	: in std_logic;
			io_hwACtrlPins_ap_done_in 	: in std_logic		

		);
	end component;

	
	component bram_tdp is
		port(
			-- Port A
			a_clk   : in  std_logic;
			a_wr    : in  std_logic;
			a_addr  : in  std_logic_vector(15 downto 0);
			a_din   : in  std_logic_vector(31 downto 0);
			a_dout  : out std_logic_vector(31 downto 0);

			-- Port B
			b_clk   : in  std_logic;
			b_wr    : in  std_logic;
			b_addr  : in  std_logic_vector(15 downto 0);
			b_din   : in  std_logic_vector(31 downto 0);
			b_dout  : out std_logic_vector(31 downto 0)
		);
	end component;	
	
	component matrixmul is
		port (
			ap_clk 		: in std_logic;
			ap_rst 		: in std_logic;
			ap_start 	: in std_logic;
			ap_done 	: out std_logic;
			ap_idle 	: out std_logic;
			ap_ready 	: out std_logic;
			a_Addr_A 	: out std_logic_vector(31 downto 0);
			a_EN_A 		: out std_logic;
			a_WEN_A 	: out std_logic_vector(3 downto 0);
			a_Din_A 	: out std_logic_vector(31 downto 0);
			a_Dout_A 	: in std_logic_vector(31 downto 0);
			a_Clk_A 	: out std_logic;
			a_Rst_A 	: out std_logic 
		);
	end component; 

	signal clk_int : std_logic;

	-- for generation of internal reset

	signal int_res            : std_logic;
	signal res_reg1, res_reg2 : std_logic;
	signal res_cnt            : unsigned(2 downto 0) := "000"; -- for the simulation

    -- sram signals for tristate inout

    signal sram_out_dout_ena : std_logic;
    signal sram_out_dout : std_logic_vector(15 downto 0);

	-- Signals for true dual port BRAM

	signal bRamCtrl_Mcmd    : std_logic_vector(2 downto 0);
	signal bRamCtrl_MAddr   : std_logic_vector(15 downto 0);
	signal bRamCtrl_MData   : std_logic_vector(31 downto 0);
	signal bRamCtrl_MByteEn : std_logic_vector(3 downto 0);
	signal bRamCtrl_SData   : std_logic_vector(31 downto 0); 

	-- Signals for HwA

	signal hwACtrl_ap_start_out : std_logic;
	signal hwACtrl_ap_reset_out : std_logic;
	signal hwACtrl_ap_ready_in 	: std_logic;
	signal hwACtrl_ap_idle_in 	: std_logic;
	signal hwACtrl_ap_done_in 	: std_logic;

	signal hwa_we   : std_logic_vector (3 downto 0);
	signal hwa_addr	: std_logic_vector (31 downto 0);
	signal hwa_in  	: std_logic_vector(31 downto 0);
	signal hwa_out 	: std_logic_vector(31 downto 0);
	signal hwa_rst 	: std_logic;

	attribute altera_attribute : string;
	attribute altera_attribute of res_cnt : signal is "POWER_UP_LEVEL=LOW";

begin
	
	clk_int <= clk;

	process(clk_int)
	begin
		if rising_edge(clk_int) then
			if (res_cnt /= "111") then
				res_cnt <= res_cnt + 1;
			end if;
			res_reg1 <= not res_cnt(0) or not res_cnt(1) or not res_cnt(2);
			res_reg2 <= res_reg1;
			int_res  <= res_reg2;
		end if;
	end process;


    -- tristate output to ssram
    process(sram_out_dout_ena, sram_out_dout)
    begin
      if sram_out_dout_ena='1' then
        SRAM_DQ <= sram_out_dout;
      else
        SRAM_DQ <= (others => 'Z');
      end if;
    end process;


    comp : Patmos port map(
		clk 	=> clk_int, 
		reset 	=> int_res,

		io_comConf_M_Cmd 		=> open, 
		io_comConf_M_Addr 		=> open, 
		io_comConf_M_Data 		=> open, 
		io_comConf_M_ByteEn 	=> open, 
		io_comConf_M_RespAccept => open,           
		io_comConf_S_Resp 		=> (others => '0'), 
		io_comConf_S_Data 		=> (others => '0'), 
		io_comConf_S_CmdAccept 	=> '0',
		io_comConf_S_Reset_n 	=> '0', 
		io_comConf_S_Flag 		=> (others => '0'), 

		io_comSpm_M_Cmd 	=> open, 
		io_comSpm_M_Addr 	=> open, 
		io_comSpm_M_Data 	=> open, 
		io_comSpm_M_ByteEn 	=> open,      
		io_comSpm_S_Resp 	=> (others => '0'), 
		io_comSpm_S_Data 	=> (others => '0'),

		io_cpuInfoPins_id 	=> X"00000000", 
		io_cpuInfoPins_cnt 	=> X"00000001",

		io_ledsPins_led 	=> oLedsPins_led,
		io_keysPins_key 	=> iKeysPins_key,    
		io_uartPins_tx 		=> oUartPins_txd, 
		io_uartPins_rx 		=> iUartPins_rxd,

		io_sramCtrlPins_ramOut_addr => oSRAM_A, 
		io_sramCtrlPins_ramOut_doutEna 	=> sram_out_dout_ena, 
		io_sramCtrlPins_ramIn_din 	=> SRAM_DQ, 
		io_sramCtrlPins_ramOut_dout => sram_out_dout, 
		io_sramCtrlPins_ramOut_nce 	=> oSRAM_CE_N, 
		io_sramCtrlPins_ramOut_noe 	=> oSRAM_OE_N, 
		io_sramCtrlPins_ramOut_nwe 	=> oSRAM_WE_N, 
		io_sramCtrlPins_ramOut_nlb 	=> oSRAM_LB_N, 
		io_sramCtrlPins_ramOut_nub 	=> oSRAM_UB_N,

		io_bRamCtrlPins_MCmd	=> bRamCtrl_Mcmd,
		io_bRamCtrlPins_MAddr   => bRamCtrl_MAddr,
		io_bRamCtrlPins_MData   => bRamCtrl_MData,
		io_bRamCtrlPins_MByteEn => bRamCtrl_MByteEn,
		io_bRamCtrlPins_SData   => bRamCtrl_SData,
			
		io_hwACtrlPins_ap_start_out	=> hwACtrl_ap_start_out,
		io_hwACtrlPins_ap_reset_out => hwACtrl_ap_reset_out,
		io_hwACtrlPins_ap_ready_in 	=> hwACtrl_ap_ready_in,
		io_hwACtrlPins_ap_idle_in 	=> hwACtrl_ap_idle_in,
		io_hwACtrlPins_ap_done_in 	=> hwACtrl_ap_done_in		

	);		
		
	bram_tdp_inst_0 : bram_tdp port map(
		-- Port A
		a_clk   => clk_int,
		a_wr    => bRamCtrl_MCmd(0),
		a_addr  => bRamCtrl_MAddr,
		a_din   => bRamCtrl_MData,
		a_dout  => bramCtrl_SData,

		-- Port B
		b_clk   => clk_int,
		b_wr    => hwa_we(0),
		b_addr  => hwa_addr(15 downto 0),
		b_din   => hwa_out,
		b_dout  => hwa_in
	);

		
	matrixmul_inst_0 : matrixmul port map(
		ap_clk 		=> clk_int,
		ap_rst 		=> hwa_rst,
		ap_start 	=> hwACtrl_ap_start_out,
		ap_done 	=> hwACtrl_ap_done_in,
		ap_idle 	=> hwACtrl_ap_idle_in,
		ap_ready 	=> hwACtrl_ap_ready_in,

		a_Addr_A 	=> hwa_addr,
		a_EN_A  	=> open,
		a_WEN_A 	=> hwa_we,
		a_Din_A  	=> hwa_out,
		a_Dout_A 	=> hwa_in,
		a_Clk_A 	=> open,
		a_Rst_A 	=> open
	);			
		
					  
	hwa_rst <= hwACtrl_ap_reset_out or int_res;		

end architecture rtl;