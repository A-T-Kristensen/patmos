library verilog;
use verilog.vl_types.all;
entity BRamCtrl is
    port(
        io_superMode    : in     vl_logic;
        io_ocp_M_Cmd    : in     vl_logic_vector(2 downto 0);
        io_ocp_M_Addr   : in     vl_logic_vector(31 downto 0);
        io_ocp_M_Data   : in     vl_logic_vector(31 downto 0);
        io_ocp_M_ByteEn : in     vl_logic_vector(3 downto 0);
        io_ocp_S_Resp   : out    vl_logic_vector(1 downto 0);
        io_ocp_S_Data   : out    vl_logic_vector(31 downto 0);
        io_bRamCtrlPins_MCmd: out    vl_logic_vector(2 downto 0);
        io_bRamCtrlPins_MAddr: out    vl_logic_vector(15 downto 0);
        io_bRamCtrlPins_MData: out    vl_logic_vector(31 downto 0);
        io_bRamCtrlPins_MByteEn: out    vl_logic_vector(3 downto 0);
        io_bRamCtrlPins_SResp: in     vl_logic_vector(1 downto 0);
        io_bRamCtrlPins_SData: in     vl_logic_vector(31 downto 0)
    );
end BRamCtrl;
