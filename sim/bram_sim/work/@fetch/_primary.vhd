library verilog;
use verilog.vl_types.all;
entity Fetch is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_ena          : in     vl_logic;
        io_fedec_instr_a: out    vl_logic_vector(31 downto 0);
        io_fedec_instr_b: out    vl_logic_vector(31 downto 0);
        io_fedec_pc     : out    vl_logic_vector(29 downto 0);
        io_fedec_base   : out    vl_logic_vector(29 downto 0);
        io_fedec_reloc  : out    vl_logic_vector(31 downto 0);
        io_fedec_relPc  : out    vl_logic_vector(29 downto 0);
        io_feex_pc      : out    vl_logic_vector(29 downto 0);
        io_exfe_doBranch: in     vl_logic;
        io_exfe_branchPc: in     vl_logic_vector(29 downto 0);
        io_memfe_doCallRet: in     vl_logic;
        io_memfe_callRetPc: in     vl_logic_vector(29 downto 0);
        io_memfe_callRetBase: in     vl_logic_vector(29 downto 0);
        io_memfe_store  : in     vl_logic;
        io_memfe_addr   : in     vl_logic_vector(31 downto 0);
        io_memfe_data   : in     vl_logic_vector(31 downto 0);
        io_feicache_addrEven: out    vl_logic_vector(31 downto 0);
        io_feicache_addrOdd: out    vl_logic_vector(31 downto 0);
        io_icachefe_instrEven: in     vl_logic_vector(31 downto 0);
        io_icachefe_instrOdd: in     vl_logic_vector(31 downto 0);
        io_icachefe_base: in     vl_logic_vector(31 downto 0);
        io_icachefe_relBase: in     vl_logic_vector(9 downto 0);
        io_icachefe_relPc: in     vl_logic_vector(10 downto 0);
        io_icachefe_reloc: in     vl_logic_vector(31 downto 0);
        io_icachefe_memSel: in     vl_logic_vector(1 downto 0)
    );
end Fetch;
