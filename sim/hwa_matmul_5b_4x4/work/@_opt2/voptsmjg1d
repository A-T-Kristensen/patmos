library verilog;
use verilog.vl_types.all;
entity OcpBurstBus is
    port(
        io_master_M_Cmd : out    vl_logic_vector(2 downto 0);
        io_master_M_Addr: out    vl_logic_vector(31 downto 0);
        io_master_M_Data: out    vl_logic_vector(31 downto 0);
        io_master_M_DataValid: out    vl_logic;
        io_master_M_DataByteEn: out    vl_logic_vector(3 downto 0);
        io_master_S_Resp: in     vl_logic_vector(1 downto 0);
        io_master_S_Data: in     vl_logic_vector(31 downto 0);
        io_master_S_CmdAccept: in     vl_logic;
        io_master_S_DataAccept: in     vl_logic;
        io_slave_M_Cmd  : in     vl_logic_vector(2 downto 0);
        io_slave_M_Addr : in     vl_logic_vector(31 downto 0);
        io_slave_M_Data : in     vl_logic_vector(31 downto 0);
        io_slave_M_DataValid: in     vl_logic;
        io_slave_M_DataByteEn: in     vl_logic_vector(3 downto 0);
        io_slave_S_Resp : out    vl_logic_vector(1 downto 0);
        io_slave_S_Data : out    vl_logic_vector(31 downto 0);
        io_slave_S_CmdAccept: out    vl_logic;
        io_slave_S_DataAccept: out    vl_logic
    );
end OcpBurstBus;
