library verilog;
use verilog.vl_types.all;
entity MCache is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_ena_out      : out    vl_logic;
        io_ena_in       : in     vl_logic;
        io_invalidate   : in     vl_logic;
        io_feicache_addrEven: in     vl_logic_vector(31 downto 0);
        io_feicache_addrOdd: in     vl_logic_vector(31 downto 0);
        io_exicache_doCallRet: in     vl_logic;
        io_exicache_callRetBase: in     vl_logic_vector(31 downto 0);
        io_exicache_callRetAddr: in     vl_logic_vector(31 downto 0);
        io_icachefe_instrEven: out    vl_logic_vector(31 downto 0);
        io_icachefe_instrOdd: out    vl_logic_vector(31 downto 0);
        io_icachefe_base: out    vl_logic_vector(31 downto 0);
        io_icachefe_relBase: out    vl_logic_vector(9 downto 0);
        io_icachefe_relPc: out    vl_logic_vector(10 downto 0);
        io_icachefe_reloc: out    vl_logic_vector(31 downto 0);
        io_icachefe_memSel: out    vl_logic_vector(1 downto 0);
        io_ocp_port_M_Cmd: out    vl_logic_vector(2 downto 0);
        io_ocp_port_M_Addr: out    vl_logic_vector(31 downto 0);
        io_ocp_port_M_Data: out    vl_logic_vector(31 downto 0);
        io_ocp_port_M_DataValid: out    vl_logic;
        io_ocp_port_M_DataByteEn: out    vl_logic_vector(3 downto 0);
        io_ocp_port_S_Resp: in     vl_logic_vector(1 downto 0);
        io_ocp_port_S_Data: in     vl_logic_vector(31 downto 0);
        io_ocp_port_S_CmdAccept: in     vl_logic;
        io_ocp_port_S_DataAccept: in     vl_logic;
        io_illMem       : out    vl_logic;
        io_perf_hit     : out    vl_logic;
        io_perf_miss    : out    vl_logic
    );
end MCache;
