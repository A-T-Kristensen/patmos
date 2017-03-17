library verilog;
use verilog.vl_types.all;
entity Patmos is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_comConf_M_Cmd: out    vl_logic_vector(2 downto 0);
        io_comConf_M_Addr: out    vl_logic_vector(31 downto 0);
        io_comConf_M_Data: out    vl_logic_vector(31 downto 0);
        io_comConf_M_ByteEn: out    vl_logic_vector(3 downto 0);
        io_comConf_M_RespAccept: out    vl_logic;
        io_comConf_S_Resp: in     vl_logic_vector(1 downto 0);
        io_comConf_S_Data: in     vl_logic_vector(31 downto 0);
        io_comConf_S_CmdAccept: in     vl_logic;
        io_comConf_S_Reset_n: in     vl_logic;
        io_comConf_S_Flag: in     vl_logic_vector(1 downto 0);
        io_comSpm_M_Cmd : out    vl_logic_vector(2 downto 0);
        io_comSpm_M_Addr: out    vl_logic_vector(31 downto 0);
        io_comSpm_M_Data: out    vl_logic_vector(31 downto 0);
        io_comSpm_M_ByteEn: out    vl_logic_vector(3 downto 0);
        io_comSpm_S_Resp: in     vl_logic_vector(1 downto 0);
        io_comSpm_S_Data: in     vl_logic_vector(31 downto 0);
        io_sRamCtrlPins_ramOut_addr: out    vl_logic_vector(19 downto 0);
        io_sRamCtrlPins_ramOut_doutEna: out    vl_logic;
        io_sRamCtrlPins_ramOut_dout: out    vl_logic_vector(15 downto 0);
        io_sRamCtrlPins_ramOut_nce: out    vl_logic;
        io_sRamCtrlPins_ramOut_noe: out    vl_logic;
        io_sRamCtrlPins_ramOut_nwe: out    vl_logic;
        io_sRamCtrlPins_ramOut_nlb: out    vl_logic;
        io_sRamCtrlPins_ramOut_nub: out    vl_logic;
        io_sRamCtrlPins_ramIn_din: in     vl_logic_vector(15 downto 0);
        io_uartPins_tx  : out    vl_logic;
        io_uartPins_rx  : in     vl_logic;
        io_ledsPins_led : out    vl_logic_vector(8 downto 0);
        io_keysPins_key : in     vl_logic_vector(3 downto 0);
        io_bRamCtrlPins_MCmd: out    vl_logic_vector(2 downto 0);
        io_bRamCtrlPins_MAddr: out    vl_logic_vector(15 downto 0);
        io_bRamCtrlPins_MData: out    vl_logic_vector(31 downto 0);
        io_bRamCtrlPins_MByteEn: out    vl_logic_vector(3 downto 0);
        io_bRamCtrlPins_SData: in     vl_logic_vector(31 downto 0);
        io_hLSControlRegPins_ap_start_out: out    vl_logic;
        io_hLSControlRegPins_ap_reset_out: out    vl_logic;
        io_hLSControlRegPins_ap_ready_in: in     vl_logic;
        io_hLSControlRegPins_ap_idle_in: in     vl_logic;
        io_hLSControlRegPins_ap_done_in: in     vl_logic;
        io_cpuInfoPins_id: in     vl_logic_vector(31 downto 0);
        io_cpuInfoPins_cnt: in     vl_logic_vector(31 downto 0)
    );
end Patmos;
