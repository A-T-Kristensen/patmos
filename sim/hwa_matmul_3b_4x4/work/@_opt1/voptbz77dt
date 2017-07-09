library verilog;
use verilog.vl_types.all;
entity StackCache is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_ena_in       : in     vl_logic;
        io_exsc_op      : in     vl_logic_vector(2 downto 0);
        io_exsc_opData  : in     vl_logic_vector(31 downto 0);
        io_exsc_opOff   : in     vl_logic_vector(31 downto 0);
        io_scex_stackTop: out    vl_logic_vector(31 downto 0);
        io_scex_memTop  : out    vl_logic_vector(31 downto 0);
        io_illMem       : out    vl_logic;
        io_stall        : out    vl_logic;
        io_fromCPU_M_Cmd: in     vl_logic_vector(2 downto 0);
        io_fromCPU_M_Addr: in     vl_logic_vector(31 downto 0);
        io_fromCPU_M_Data: in     vl_logic_vector(31 downto 0);
        io_fromCPU_M_ByteEn: in     vl_logic_vector(3 downto 0);
        io_fromCPU_S_Resp: out    vl_logic_vector(1 downto 0);
        io_fromCPU_S_Data: out    vl_logic_vector(31 downto 0);
        io_toMemory_M_Cmd: out    vl_logic_vector(2 downto 0);
        io_toMemory_M_Addr: out    vl_logic_vector(31 downto 0);
        io_toMemory_M_Data: out    vl_logic_vector(31 downto 0);
        io_toMemory_M_DataValid: out    vl_logic;
        io_toMemory_M_DataByteEn: out    vl_logic_vector(3 downto 0);
        io_toMemory_S_Resp: in     vl_logic_vector(1 downto 0);
        io_toMemory_S_Data: in     vl_logic_vector(31 downto 0);
        io_toMemory_S_CmdAccept: in     vl_logic;
        io_toMemory_S_DataAccept: in     vl_logic;
        io_perf_spill   : out    vl_logic;
        io_perf_fill    : out    vl_logic
    );
end StackCache;
