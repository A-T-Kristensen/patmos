library verilog;
use verilog.vl_types.all;
entity MCacheReplFifo is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_ena_in       : in     vl_logic;
        io_invalidate   : in     vl_logic;
        io_hitEna       : out    vl_logic;
        io_exmcache_doCallRet: in     vl_logic;
        io_exmcache_callRetBase: in     vl_logic_vector(31 downto 0);
        io_exmcache_callRetAddr: in     vl_logic_vector(31 downto 0);
        io_mcachefe_instrEven: out    vl_logic_vector(31 downto 0);
        io_mcachefe_instrOdd: out    vl_logic_vector(31 downto 0);
        io_mcachefe_base: out    vl_logic_vector(31 downto 0);
        io_mcachefe_relBase: out    vl_logic_vector(9 downto 0);
        io_mcachefe_relPc: out    vl_logic_vector(10 downto 0);
        io_mcachefe_reloc: out    vl_logic_vector(31 downto 0);
        io_mcachefe_memSel: out    vl_logic_vector(1 downto 0);
        io_ctrlrepl_wEna: in     vl_logic;
        io_ctrlrepl_wData: in     vl_logic_vector(31 downto 0);
        io_ctrlrepl_wAddr: in     vl_logic_vector(31 downto 0);
        io_ctrlrepl_wTag: in     vl_logic;
        io_ctrlrepl_addrEven: in     vl_logic_vector(9 downto 0);
        io_ctrlrepl_addrOdd: in     vl_logic_vector(9 downto 0);
        io_ctrlrepl_instrStall: in     vl_logic;
        io_replctrl_hit : out    vl_logic;
        io_memIn_wEven  : out    vl_logic;
        io_memIn_wOdd   : out    vl_logic;
        io_memIn_wData  : out    vl_logic_vector(31 downto 0);
        io_memIn_wAddr  : out    vl_logic_vector(8 downto 0);
        io_memIn_addrEven: out    vl_logic_vector(8 downto 0);
        io_memIn_addrOdd: out    vl_logic_vector(8 downto 0);
        io_memOut_instrEven: in     vl_logic_vector(31 downto 0);
        io_memOut_instrOdd: in     vl_logic_vector(31 downto 0);
        io_perf_hit     : out    vl_logic;
        io_perf_miss    : out    vl_logic
    );
end MCacheReplFifo;
