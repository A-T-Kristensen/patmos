library verilog;
use verilog.vl_types.all;
entity SSRam32Ctrl is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_ocp_M_Cmd    : in     vl_logic_vector(2 downto 0);
        io_ocp_M_Addr   : in     vl_logic_vector(20 downto 0);
        io_ocp_M_Data   : in     vl_logic_vector(31 downto 0);
        io_ocp_M_DataValid: in     vl_logic;
        io_ocp_M_DataByteEn: in     vl_logic_vector(3 downto 0);
        io_ocp_S_Resp   : out    vl_logic_vector(1 downto 0);
        io_ocp_S_Data   : out    vl_logic_vector(31 downto 0);
        io_ocp_S_CmdAccept: out    vl_logic;
        io_ocp_S_DataAccept: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_addr: out    vl_logic_vector(18 downto 0);
        io_sSRam32CtrlPins_ramOut_doutEna: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_nadsc: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_noe: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_nbwe: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_nbw: out    vl_logic_vector(3 downto 0);
        io_sSRam32CtrlPins_ramOut_ngw: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_nce1: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_ce2: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_nce3: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_nadsp: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_nadv: out    vl_logic;
        io_sSRam32CtrlPins_ramOut_dout: out    vl_logic_vector(31 downto 0);
        io_sSRam32CtrlPins_ramIn_din: in     vl_logic_vector(31 downto 0)
    );
end SSRam32Ctrl;
