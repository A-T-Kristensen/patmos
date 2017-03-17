library verilog;
use verilog.vl_types.all;
entity Keys is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_superMode    : in     vl_logic;
        io_ocp_M_Cmd    : in     vl_logic_vector(2 downto 0);
        io_ocp_M_Addr   : in     vl_logic_vector(31 downto 0);
        io_ocp_M_Data   : in     vl_logic_vector(31 downto 0);
        io_ocp_M_ByteEn : in     vl_logic_vector(3 downto 0);
        io_ocp_S_Resp   : out    vl_logic_vector(1 downto 0);
        io_ocp_S_Data   : out    vl_logic_vector(31 downto 0);
        io_keysPins_key : in     vl_logic_vector(3 downto 0);
        io_keysIntrs_3  : out    vl_logic;
        io_keysIntrs_2  : out    vl_logic;
        io_keysIntrs_1  : out    vl_logic;
        io_keysIntrs_0  : out    vl_logic
    );
end Keys;
