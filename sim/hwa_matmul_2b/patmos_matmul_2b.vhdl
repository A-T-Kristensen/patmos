--
-- Copyright: 2013, Technical University of Denmark, DTU Compute
-- Author: Martin Schoeberl (martin@jopdesign.com)
--         Rasmus Bo Soerensen (rasmus@rbscloud.dk)
-- License: Simplified BSD License
--

-- VHDL top level for Patmos in Chisel on Altera de2-115 board
--
-- Includes some 'magic' VHDL code to generate a reset after FPGA configuration.
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use IEEE.math_real."ceil";
use IEEE.math_real."log2";
use work.HWA_PACKAGE.all;

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

			io_hwACtrlPins_ap_start_out 	: out std_logic;
			io_hwACtrlPins_ap_reset_out 	: out std_logic;
			io_hwACtrlPins_ap_ready_in 	: in std_logic;
			io_hwACtrlPins_ap_idle_in 	: in std_logic;
			io_hwACtrlPins_ap_done_in 	: in std_logic		

		);
	end component;

	component n_bank is
		port (
		    clk     : in  std_logic;

		    -- Patmos side this is always the same
		    p_we    : in  std_logic;
		    p_addr  : in  std_logic_vector(ADDR_WIDTH - 1 downto 0); -- The upper bits are used to select bank.
		    p_dout  : in  std_logic_vector(DATA_WIDTH - 1 downto 0);
		    p_din   : out std_logic_vector(DATA_WIDTH - 1 downto 0);    -- Input to patmos

		    -- HwA HLS Side, this is parametized
	        bram_m : in bank_master_a;
	        bram_s : out bank_slave_a       
		);
	end component;  
	
	component matrixmul is
	port (
	    ap_clk : IN STD_LOGIC;
	    ap_rst : IN STD_LOGIC;
	    ap_start : IN STD_LOGIC;
	    ap_done : OUT STD_LOGIC;
	    ap_idle : OUT STD_LOGIC;
	    ap_ready : OUT STD_LOGIC;
	    a_0_Addr_A : OUT STD_LOGIC_VECTOR (31 downto 0);
	    a_0_EN_A : OUT STD_LOGIC;
	    a_0_WEN_A : OUT STD_LOGIC_VECTOR (3 downto 0);
	    a_0_Din_A : OUT STD_LOGIC_VECTOR (31 downto 0);
	    a_0_Dout_A : IN STD_LOGIC_VECTOR (31 downto 0);
	    a_0_Clk_A : OUT STD_LOGIC;
	    a_0_Rst_A : OUT STD_LOGIC;
	    a_1_Addr_A : OUT STD_LOGIC_VECTOR (31 downto 0);
	    a_1_EN_A : OUT STD_LOGIC;
	    a_1_WEN_A : OUT STD_LOGIC_VECTOR (3 downto 0);
	    a_1_Din_A : OUT STD_LOGIC_VECTOR (31 downto 0);
	    a_1_Dout_A : IN STD_LOGIC_VECTOR (31 downto 0);
	    a_1_Clk_A : OUT STD_LOGIC;
	    a_1_Rst_A : OUT STD_LOGIC );
	end component;

	signal clk_int : std_logic;

	-- for generation of internal reset

	signal int_res            : std_logic;
	signal res_reg1, res_reg2 : std_logic;
	signal res_cnt            : unsigned(2 downto 0) := "000"; -- for the simulation

    -- sram signals for tristate inout

    signal sram_out_dout_ena : std_logic;
    signal sram_out_dout : std_logic_vector(15 downto 0);

	-- Signals for true dual port bram

	signal bRamCtrl_Mcmd    : std_logic_vector(2 downto 0);
	signal bRamCtrl_MAddr   : std_logic_vector(15 downto 0);
	signal bRamCtrl_MData   : std_logic_vector(31 downto 0);
	signal bRamCtrl_MByteEn : std_logic_vector(3 downto 0);
	signal bRamCtrl_SData   : std_logic_vector(31 downto 0); 

	-- Signals for hls accel

	signal hwACtrl_ap_start_out 	: std_logic;
	signal hwACtrl_ap_reset_out 	: std_logic;
	signal hwACtrl_ap_ready_in 	: std_logic;
	signal hwACtrl_ap_idle_in 	: std_logic;
	signal hwACtrl_ap_done_in 	: std_logic;

    signal bram_m_i : bank_master_a;
    signal bram_s_i: bank_slave_a;	
    signal hwa_addr_i : hwa_addr_a;

	signal hlsReset : std_logic;

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
		io_hwACtrlPins_ap_reset_out 	=> hwACtrl_ap_reset_out,
		io_hwACtrlPins_ap_ready_in 	=> hwACtrl_ap_ready_in,
		io_hwACtrlPins_ap_idle_in 	=> hwACtrl_ap_idle_in,
		io_hwACtrlPins_ap_done_in 	=> hwACtrl_ap_done_in		

	);		

	n_bank_inst_0 : n_bank port map (

	    clk     => clk_int,

	    -- Patmos side
	    p_we    => bRamCtrl_MCmd(0),
	    p_addr  => bRamCtrl_MAddr,  -- The upper bits are used to select bank.
	    p_dout  => bRamCtrl_MData,
	    p_din   => bramCtrl_SData,-- Input to patmos

	    -- HLS Side
        bram_m => bram_m_i,
        bram_s  => bram_s_i
	);
		
	matrixmul_inst_0 : matrixmul port map(
		ap_clk 		=> clk_int,
		ap_rst 		=> hlsReset,
		ap_start 	=> hwACtrl_ap_start_out,
		ap_done 	=> hwACtrl_ap_done_in,
		ap_idle 	=> hwACtrl_ap_idle_in,
		ap_ready 	=> hwACtrl_ap_ready_in,

		a_0_Addr_A 	=> hwa_addr_i(0).addr,
		a_0_EN_A  	=> open,
		a_0_WEN_A	=> bram_m_i(0).wr,
		a_0_Din_A  	=> bram_m_i(0).din,
		a_0_Dout_A 	=> bram_s_i(0).dout,
		a_0_Clk_A 	=> open,
		a_0_Rst_A 	=> open,

		a_1_Addr_A 	=> hwa_addr_i(1).addr,
		a_1_EN_A  	=> open,
		a_1_WEN_A 	=> bram_m_i(1).wr,
		a_1_Din_A  	=> bram_m_i(1).din,
		a_1_Dout_A 	=> bram_s_i(1).dout,
		a_1_Clk_A 	=> open,
		a_1_Rst_A 	=> open
	);			
							  
	hlsReset <= hwACtrl_ap_reset_out or int_res;		

	addr_map:
	for i in (NBANKS-1) downto 0 generate
	    	bram_m_i(i).addr <= hwa_addr_i(i).addr(ADDR_BITS - 1 downto 0);
    end generate;

end architecture rtl;