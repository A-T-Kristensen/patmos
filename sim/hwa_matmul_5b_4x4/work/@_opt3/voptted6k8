library verilog;
use verilog.vl_types.all;
entity SRamCtrl is
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
        io_sRamCtrlPins_ramOut_addr: out    vl_logic_vector(19 downto 0);
        io_sRamCtrlPins_ramOut_doutEna: out    vl_logic;
        io_sRamCtrlPins_ramOut_dout: out    vl_logic_vector(15 downto 0);
        io_sRamCtrlPins_ramOut_nce: out    vl_logic;
        io_sRamCtrlPins_ramOut_noe: out    vl_logic;
        io_sRamCtrlPins_ramOut_nwe: out    vl_logic;
        io_sRamCtrlPins_ramOut_nlb: out    vl_logic;
        io_sRamCtrlPins_ramOut_nub: out    vl_logic;
        io_sRamCtrlPins_ramIn_din: in     vl_logic_vector(15 downto 0)
    );
end SRamCtrl;
