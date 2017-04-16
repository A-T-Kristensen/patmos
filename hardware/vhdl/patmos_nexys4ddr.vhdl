--
-- Copyright: 2013, Technical University of Denmark, DTU Compute
-- Author: Luca Pezzarossa (lpez@dtu.dk)
--		   Andreas T. Kristensen (s144026@student.dtu.dk)
-- License: Simplified BSD License
--
--
-- VHDL top level for Patmos on the Digilent/Xilinx Nexys4DDR board with off-chip memory
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity patmos_top is
	port(
		clk_in               : in    std_logic;
		cpu_reset_btn        : in    std_logic;

		green_leds           : out   std_logic_vector(15 downto 0); -- (15) -> LD15 ... LD0 <- (0)
		rgb_leds             : out   std_logic_vector(5 downto 0); 	-- (5) -> LD17_R LD17_G LD17_B | LD16_R LD16_G LD16_B <- (0)
		seven_segments       : out   std_logic_vector(7 downto 0); 	-- (7) -> DP CG CF CE CD CC CB CA <- (0)
		seven_segments_drive : out   std_logic_vector(7 downto 0); 	-- (7) -> AN7 ... AN0 <- (0)
		buttons              : in    std_logic_vector(4 downto 0); 	-- (4) -> BTNT BTNR BTND BTNL BTNC <- (0)
		switches             : in    std_logic_vector(15 downto 0); -- (15) -> SW15 ... SW0 <- (0)

		--TXD, RXD naming uses terminal-centric naming convention
		uart_txd    : in    std_logic;
		uart_rxd    : out   std_logic;

		--DDR2 pins
		ddr2_dq     : inout std_logic_vector(15 downto 0);
		ddr2_dqs_n  : inout std_logic_vector(1 downto 0);
		ddr2_dqs_p  : inout std_logic_vector(1 downto 0);
		ddr2_addr   : out   std_logic_vector(12 downto 0);
		ddr2_ba     : out   std_logic_vector(2 downto 0);
		ddr2_ras_n  : out   std_logic;
		ddr2_cas_n  : out   std_logic;
		ddr2_we_n   : out   std_logic;
		ddr2_ck_p   : out   std_logic_vector(0 to 0);
		ddr2_ck_n   : out   std_logic_vector(0 to 0);
		ddr2_cke    : out   std_logic_vector(0 to 0);
		ddr2_cs_n   : out   std_logic_vector(0 to 0);
		ddr2_dm     : out   std_logic_vector(1 downto 0);
		ddr2_odt	: out   std_logic_vector(0 to 0)
	);
end entity patmos_top;

architecture rtl of patmos_top is
	component Patmos is
		port(
			clk     : in  std_logic;
			reset   : in  std_logic;

			io_comConf_M_Cmd              : out std_logic_vector(2 downto 0);
			io_comConf_M_Addr             : out std_logic_vector(31 downto 0);
			io_comConf_M_Data             : out std_logic_vector(31 downto 0);
			io_comConf_M_ByteEn           : out std_logic_vector(3 downto 0);
			io_comConf_M_RespAccept       : out std_logic;
			io_comConf_S_Resp             : in  std_logic_vector(1 downto 0);
			io_comConf_S_Data             : in  std_logic_vector(31 downto 0);
			io_comConf_S_CmdAccept        : in  std_logic;
            io_comConf_S_Reset_n          : in  std_logic;
            io_comConf_S_Flag             : in  std_logic_vector(1 downto 0);

			io_comSpm_M_Cmd     : out std_logic_vector(2 downto 0);
			io_comSpm_M_Addr    : out std_logic_vector(31 downto 0);
			io_comSpm_M_Data    : out std_logic_vector(31 downto 0);
			io_comSpm_M_ByteEn  : out std_logic_vector(3 downto 0);
			io_comSpm_S_Resp    : in  std_logic_vector(1 downto 0);
			io_comSpm_S_Data	: in  std_logic_vector(31 downto 0);

			io_memBridgePins_M_Cmd        : out std_logic_vector(2 downto 0);
			io_memBridgePins_M_Addr       : out std_logic_vector(31 downto 0);
			io_memBridgePins_M_Data       : out std_logic_vector(31 downto 0);
			io_memBridgePins_M_DataValid  : out std_logic;
			io_memBridgePins_M_DataByteEn : out std_logic_vector(3 downto 0);
			io_memBridgePins_S_Resp       : in  std_logic_vector(1 downto 0);
			io_memBridgePins_S_Data       : in  std_logic_vector(31 downto 0);
			io_memBridgePins_S_CmdAccept  : in  std_logic;
			io_memBridgePins_S_DataAccept : in  std_logic;

			io_cpuInfoPins_id   : in  std_logic_vector(31 downto 0);
			io_cpuInfoPins_cnt  : in  std_logic_vector(31 downto 0);
			io_uartPins_tx      : out std_logic;
			io_uartPins_rx		: in  std_logic;

			io_nexys4DDRIOPins_MCmd       : out std_logic_vector(2 downto 0);
			io_nexys4DDRIOPins_MAddr      : out std_logic_vector(15 downto 0);
			io_nexys4DDRIOPins_MData      : out std_logic_vector(31 downto 0);
			io_nexys4DDRIOPins_MByteEn    : out std_logic_vector(3 downto 0);
			io_nexys4DDRIOPins_SResp      : in  std_logic_vector(1 downto 0);
			io_nexys4DDRIOPins_SData      : in  std_logic_vector(31 downto 0);
			
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

	component nexys4ddr_io is
		port(
			clk     : in  std_logic;
			clk_pwm : in  std_logic;
			reset   : in  std_logic;

			MCmd    : in  std_logic_vector(2 downto 0);
			MAddr   : in  std_logic_vector(15 downto 0);
			MData   : in  std_logic_vector(31 downto 0);
			MByteEn : in  std_logic_vector(3 downto 0);
			SResp   : out std_logic_vector(1 downto 0);
			SData 	: out std_logic_vector(31 downto 0);

			green_leds           : out std_logic_vector(15 downto 0); 	-- (15) -> LD15 ... LD0 <- (0)
			rgb_leds             : out std_logic_vector(5 downto 0); 	-- (5) -> LD17_R LD17_G LD17_B | LD16_R LD16_G LD16_B <- (0)
			seven_segments       : out std_logic_vector(7 downto 0); 	-- (7) -> DP CG CF CE CD CC CB CA <- (0)
			seven_segments_drive : out std_logic_vector(7 downto 0); 	-- (7) -> AN7 ... AN0 <- (0)
			buttons              : in  std_logic_vector(4 downto 0); 	-- (4) -> BTNT BTNR BTND BTNL BTNC <- (0)
			switches             : in  std_logic_vector(15 downto 0)); 	-- (15) -> SW15 ... SW0 <- (0)
	end component;

	component ddr2_ctrl is
		port(
			ddr2_dq 	: inout std_logic_vector(15 downto 0);
			ddr2_dqs_n  : inout std_logic_vector(1 downto 0);
			ddr2_dqs_p  : inout std_logic_vector(1 downto 0);
			ddr2_addr   : out   std_logic_vector(12 downto 0);
			ddr2_ba     : out   std_logic_vector(2 downto 0);
			ddr2_ras_n  : out   std_logic;
			ddr2_cas_n  : out   std_logic;
			ddr2_we_n   : out   std_logic;
			ddr2_ck_p   : out   std_logic_vector(0 to 0);
			ddr2_ck_n   : out   std_logic_vector(0 to 0);
			ddr2_cke    : out   std_logic_vector(0 to 0);
			ddr2_cs_n   : out   std_logic_vector(0 to 0);
			ddr2_dm     : out   std_logic_vector(1 downto 0);
			ddr2_odt    : out   std_logic_vector(0 to 0);

			sys_clk_i           : in    std_logic;
			app_addr            : in    std_logic_vector(26 downto 0);
			app_cmd             : in    std_logic_vector(2 downto 0);
			app_en              : in    std_logic;
			app_wdf_data        : in    std_logic_vector(127 downto 0);
			app_wdf_end         : in    std_logic;
			app_wdf_mask        : in    std_logic_vector(15 downto 0);
			app_wdf_wren        : in    std_logic;
			app_rd_data         : out   std_logic_vector(127 downto 0);
			app_rd_data_end     : out   std_logic;
			app_rd_data_valid   : out   std_logic;
			app_rdy             : out   std_logic;
			app_wdf_rdy         : out   std_logic;
			app_sr_req          : in    std_logic;
			app_ref_req         : in    std_logic;
			app_zq_req          : in    std_logic;
			app_sr_active       : out   std_logic;
			app_ref_ack         : out   std_logic;
			app_zq_ack          : out   std_logic;
			ui_clk              : out   std_logic;
			ui_clk_sync_rst     : out   std_logic;
			init_calib_complete : out   std_logic;
			sys_rst             : in    std_logic
		);
	end component;

	component ocp_burst_to_ddr2_ctrl is
		port(
			-- Common
			clk     : in  std_logic;
			rst 	: in  std_logic;

			-- OCPburst in (slave)
			MCmd            : in  std_logic_vector(2 downto 0);
			MAddr           : in  std_logic_vector(31 downto 0);
			MData           : in  std_logic_vector(31 downto 0);
			MDataValid      : in  std_logic;
			MDataByteEn     : in  std_logic_vector(3 downto 0);
			SResp           : out std_logic_vector(1 downto 0);
			SData           : out std_logic_vector(31 downto 0);
			SCmdAccept      : out std_logic;
			SDataAccept 	: out std_logic;

			-- Xilinx interface
			app_addr          : out std_logic_vector(26 downto 0);
			app_cmd           : out std_logic_vector(2 downto 0);
			app_en            : out std_logic;
			app_wdf_data      : out std_logic_vector(127 downto 0);
			app_wdf_end       : out std_logic;
			app_wdf_mask      : out std_logic_vector(15 downto 0);
			app_wdf_wren      : out std_logic;
			app_rd_data       : in  std_logic_vector(127 downto 0);
			app_rd_data_end   : in  std_logic;
			app_rd_data_valid : in  std_logic;
			app_rdy           : in  std_logic;
			app_wdf_rdy       : in  std_logic
		);
	end component;
	
	component bram_tdp is
		port (
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
			a_Addr_A 	: out std_logic_vector (31 downto 0);
			a_EN_A 		: out std_logic;
			a_WEN_A 	: out std_logic_vector (3 downto 0);
			a_Din_A 	: out std_logic_vector (31 downto 0);
			a_Dout_A 	: in std_logic_vector (31 downto 0);
			a_Clk_A 	: out std_logic;
			a_Rst_A 	: out std_logic );
end component; 	

	component clk_manager is
		port(
			clk_in    : in  std_logic;
			clk_out_1 : out std_logic;
			clk_out_2 : out std_logic;
			locked    : out std_logic
		);
	end component;

	signal clk_int : std_logic;
	signal clk_200 : std_logic;
	signal clk_pwm : std_logic;

	-- for generation of internal reset

	signal reset_int, reset_ddr         : std_logic;
	signal res_reg1, res_reg2, res_reg3, res_reg4 : std_logic;
	signal locked                                 : std_logic;
	signal cpu_reset_btn_debounced, cpu_reset_btn_prev, cpu_reset_btn_sync_int, cpu_reset_btn_sync : std_logic;
    signal debounce_count  : unsigned(12 downto 0);
    constant DEBOUNCE_TIME : integer := 8000;

	-- signals for nexys4DDRIO

	signal nexys4DDRIO_MCmd    : std_logic_vector(2 downto 0);
	signal nexys4DDRIO_MAddr   : std_logic_vector(15 downto 0);
	signal nexys4DDRIO_MData   : std_logic_vector(31 downto 0);
	signal nexys4DDRIO_MByteEn : std_logic_vector(3 downto 0);
	signal nexys4DDRIO_SResp   : std_logic_vector(1 downto 0);
	signal nexys4DDRIO_SData   : std_logic_vector(31 downto 0);

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

	signal hwa_we   : std_logic_vector (3 downto 0);
	signal hwa_addr   : std_logic_vector (31 downto 0);
	signal hwa_in   : std_logic_vector(31 downto 0);
	signal hwa_out : std_logic_vector(31 downto 0);
	signal hwa_rst : std_logic;	

	-- signals for the bridge

	signal MCmd_bridge        : std_logic_vector(2 downto 0);
	signal MAddr_bridge       : std_logic_vector(31 downto 0);
	signal MData_bridge       : std_logic_vector(31 downto 0);
	signal MDataValid_bridge  : std_logic;
	signal MDataByteEn_bridge : std_logic_vector(3 downto 0);
	signal SResp_bridge       : std_logic_vector(1 downto 0);
	signal SData_bridge       : std_logic_vector(31 downto 0);
	signal SCmdAccept_bridge  : std_logic;
	signal SDataAccept_bridge : std_logic;

	signal app_addr_bridge          : std_logic_vector(26 downto 0); 
	signal app_cmd_bridge           : std_logic_vector(2 downto 0); 
	signal app_en_bridge            : std_logic;
	signal app_wdf_data_bridge      : std_logic_vector(127 downto 0);
	signal app_wdf_end_bridge       : std_logic;
	signal app_wdf_mask_bridge      : std_logic_vector(15 downto 0);
	signal app_wdf_wren_bridge      : std_logic;
	signal app_rd_data_bridge       : std_logic_vector(127 downto 0); 
	signal app_rd_data_end_bridge   : std_logic; 
	signal app_rd_data_valid_bridge : std_logic;
	signal app_rdy_bridge           : std_logic;
	signal app_wdf_rdy_bridge       : std_logic;

	--------------------------------------
	-- 	ATTRIBUTE FIELDS FOR SIGNALS 	--
	--------------------------------------

	-- If you want to declare an attribute for a signal, component or architecture, define it after
	-- you define your signal, component etc.

	-- Works on nexys4 ddr with dont_touch on hwa_addr and hwa_addr_resized with process.
	-- can just index hwa_addr, without hwa_addr_resized, if we use dont_touch :)

	-- SIGNALS THAT SHOULD NOT BE TOUCH

	attribute dont_touch : string;  

	attribute dont_touch of hwa_addr 	: signal is "true";		

	------------------------------
	-- 	SIGNALS FOR DEBUGGING	--
	------------------------------

	-- Uncomment these if you want to debug them using Vivado

    --attribute mark_debug : string;
  
    --attribute mark_debug of bRamCtrl_MCmd 	: signal is "true";
    --attribute mark_debug of bRamCtrl_MAddr  : signal is "true";
    --attribute mark_debug of bRamCtrl_MData  : signal is "true";
    --attribute mark_debug of bramCtrl_SData 	: signal is "true";

      
    --attribute mark_debug of hwACtrl_ap_reset_out 	: signal is "true";
    --attribute mark_debug of hwACtrl_ap_start_out    : signal is "true";
    --attribute mark_debug of hwACtrl_ap_done_in      : signal is "true";
    --attribute mark_debug of hwACtrl_ap_idle_in      : signal is "true";
    --attribute mark_debug of hwACtrl_ap_ready_in     : signal is "true";

	--attribute mark_debug of hwa_we             	: signal is "true";
	--attribute mark_debug of hwa_addr         		: signal is "true";	
	--attribute mark_debug of hwa_in             	: signal is "true";	
	--attribute mark_debug of hwa_out            	: signal is "true";	
	--attribute mark_debug of hwa_rst          	: signal is "true";

 	--attribute mark_debug of reset_int : signal is "true";	

begin

	clk_manager_inst_0 : clk_manager port map(
			clk_in    => clk_in,
			clk_out_1 => clk_200,
			clk_out_2 => clk_pwm,
			locked    => locked
		);

    --  reset button debouncer
	rst_btn_debouncer_PROC : process(clk_200)
	begin
		if rising_edge(clk_200) then
			if locked = '0' then
				debounce_count          <= (others => '0');
				cpu_reset_btn_debounced <= '0';
				cpu_reset_btn_prev      <= '0';
				cpu_reset_btn_sync      <= '0';
				cpu_reset_btn_sync_int  <= '0';
			else
				cpu_reset_btn_sync     <= cpu_reset_btn_sync_int;
				cpu_reset_btn_sync_int <= cpu_reset_btn;
				if (cpu_reset_btn_sync = cpu_reset_btn_prev) then
					if (debounce_count = DEBOUNCE_TIME) then
						cpu_reset_btn_debounced <= cpu_reset_btn_prev;
					else
						debounce_count <= debounce_count + 1;
					end if;
				else
					debounce_count     <= (others => '0');
					cpu_reset_btn_prev <= cpu_reset_btn_sync;
				end if;
			end if;
		end if;
	end process;
	
	--  internal reset generation
	process(clk_200)
	begin
		if rising_edge(clk_200) then
			res_reg1 <= locked and cpu_reset_btn_debounced;
			res_reg2 <= res_reg1;
			reset_ddr  <= res_reg2;
		end if;
	end process;

	ocp_burst_to_ddr2_ctrl_inst_0 : ocp_burst_to_ddr2_ctrl port map(
			clk               => clk_int,
			rst               => reset_int, -- --            : in std_logic; -- (=1 is reset)

			-- OCPburst in (slave)
			MCmd              => MCmd_bridge, 
			MAddr             => MAddr_bridge, 
			MData             => MData_bridge, 
			MDataValid        => MDataValid_bridge, 
			MDataByteEn       => MDataByteEn_bridge, 
			SResp             => SResp_bridge, 
			SData             => SData_bridge, 
			SCmdAccept        => SCmdAccept_bridge, 
			SDataAccept       => SDataAccept_bridge, 

			-- Xilinx interface
			app_addr          => app_addr_bridge, 
			app_cmd           => app_cmd_bridge, 
			app_en            => app_en_bridge, 
			app_wdf_data      => app_wdf_data_bridge, 
			app_wdf_end       => app_wdf_end_bridge, 
			app_wdf_mask      => app_wdf_mask_bridge, 
			app_wdf_wren      => app_wdf_wren_bridge, 
			app_rd_data       => app_rd_data_bridge, 
			app_rd_data_end   => app_rd_data_end_bridge, 
			app_rd_data_valid => app_rd_data_valid_bridge, 
			app_rdy           => app_rdy_bridge, 
			app_wdf_rdy       => app_wdf_rdy_bridge 
		);

	ddr2_ctrl_inst_0 : ddr2_ctrl port map(
			ddr2_dq             => ddr2_dq, 
			ddr2_dqs_n          => ddr2_dqs_n, 
			ddr2_dqs_p          => ddr2_dqs_p, 
			ddr2_addr           => ddr2_addr, 
			ddr2_ba             => ddr2_ba, 
			ddr2_ras_n          => ddr2_ras_n, 
			ddr2_cas_n          => ddr2_cas_n, 
			ddr2_we_n           => ddr2_we_n, 
			ddr2_ck_p           => ddr2_ck_p, 
			ddr2_ck_n           => ddr2_ck_n, 
			ddr2_cke            => ddr2_cke, 
			ddr2_cs_n           => ddr2_cs_n, 
			ddr2_dm             => ddr2_dm, 
			ddr2_odt            => ddr2_odt,
			sys_clk_i           => clk_200, 
			app_addr            => app_addr_bridge, 
			app_cmd             => app_cmd_bridge, 
			app_en              => app_en_bridge, 
			app_wdf_data        => app_wdf_data_bridge, 
			app_wdf_end         => app_wdf_end_bridge, 
			app_wdf_mask        => app_wdf_mask_bridge,
			app_wdf_wren        => app_wdf_wren_bridge, 
			app_rd_data         => app_rd_data_bridge, 
			app_rd_data_end     => app_rd_data_end_bridge,
			app_rd_data_valid   => app_rd_data_valid_bridge,
			app_rdy             => app_rdy_bridge,
			app_wdf_rdy         => app_wdf_rdy_bridge,
			app_sr_req          => '0',
			app_ref_req         => '0',
			app_zq_req          => '0',
			app_sr_active       => open,
			app_ref_ack         => open,
			app_zq_ack          => open,
			ui_clk              => clk_int,
			ui_clk_sync_rst     => reset_int,
			init_calib_complete => open,
			sys_rst             => reset_ddr
		);

	-- The instance of the patmos processor            
	patmos_inst_0 : Patmos port map(
			clk                           => clk_int,
			reset                         => reset_int,
			io_comConf_M_Cmd              => open,
			io_comConf_M_Addr             => open,
			io_comConf_M_Data             => open,
			io_comConf_M_ByteEn           => open,
			io_comConf_M_RespAccept       => open,
			io_comConf_S_Resp             => (others => '0'),
			io_comConf_S_Data             => (others => '0'),
			io_comConf_S_CmdAccept        => '0',
			io_comConf_S_Reset_n          => '0',
            io_comConf_S_Flag             => (others => '0'),
			io_comSpm_M_Cmd               => open,
			io_comSpm_M_Addr              => open,
			io_comSpm_M_Data              => open,
			io_comSpm_M_ByteEn            => open,
			io_comSpm_S_Resp              => (others => '0'),
			io_comSpm_S_Data              => (others => '0'),
			io_memBridgePins_M_Cmd        => MCmd_bridge,
			io_memBridgePins_M_Addr       => MAddr_bridge,
			io_memBridgePins_M_Data       => MData_bridge,
			io_memBridgePins_M_DataValid  => MDataValid_bridge,
			io_memBridgePins_M_DataByteEn => MDataByteEn_bridge,
			io_memBridgePins_S_Resp       => SResp_bridge,
			io_memBridgePins_S_Data       => SData_bridge,
			io_memBridgePins_S_CmdAccept  => SCmdAccept_bridge,
			io_memBridgePins_S_DataAccept => SDataAccept_bridge,

			io_cpuInfoPins_id             => X"00000000",
			io_cpuInfoPins_cnt            => X"00000000",
			
			-- TXD, RXD naming uses terminal-centric naming convention
			io_uartPins_tx                => uart_rxd,
			io_uartPins_rx                => uart_txd,

			io_nexys4DDRIOPins_MCmd       => nexys4DDRIO_MCmd,
			io_nexys4DDRIOPins_MAddr      => nexys4DDRIO_MAddr,
			io_nexys4DDRIOPins_MData      => nexys4DDRIO_MData,
			io_nexys4DDRIOPins_MByteEn    => nexys4DDRIO_MByteEn,
			io_nexys4DDRIOPins_SResp      => nexys4DDRIO_SResp,
			io_nexys4DDRIOPins_SData      => nexys4DDRIO_SData,
		
			io_bRamCtrlPins_MCmd       => bRamCtrl_Mcmd,
			io_bRamCtrlPins_MAddr      => bRamCtrl_MAddr,
			io_bRamCtrlPins_MData      => bRamCtrl_MData,
			io_bRamCtrlPins_MByteEn    => bRamCtrl_MByteEn,
			io_bRamCtrlPins_SData      => bRamCtrl_SData,
		
			io_hwACtrlPins_ap_start_out 	=> hwACtrl_ap_start_out,
			io_hwACtrlPins_ap_reset_out 	=> hwACtrl_ap_reset_out,
			io_hwACtrlPins_ap_ready_in 	=> hwACtrl_ap_ready_in,
			io_hwACtrlPins_ap_idle_in 	=> hwACtrl_ap_idle_in,
			io_hwACtrlPins_ap_done_in 	=> hwACtrl_ap_done_in
		);

	nexys4ddr_io_inst_0 : nexys4ddr_io port map(
			clk                  => clk_int,
			clk_pwm              => clk_pwm,
			reset                => reset_int,

			MCmd                 => nexys4DDRIO_MCmd,
			MAddr                => nexys4DDRIO_MAddr,
			MData                => nexys4DDRIO_MData,
			MByteEn              => nexys4DDRIO_MByteEn,
			SResp                => nexys4DDRIO_SResp,
			SData                => nexys4DDRIO_SData,

			green_leds           => green_leds,
			rgb_leds             => rgb_leds,
			seven_segments       => seven_segments,
			seven_segments_drive => seven_segments_drive,
			buttons              => buttons,
			switches             => switches
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

	hwa_rst 		<= hwACtrl_ap_reset_out or reset_int;		
					  				
end architecture rtl;