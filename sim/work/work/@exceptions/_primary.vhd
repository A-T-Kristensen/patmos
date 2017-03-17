library verilog;
use verilog.vl_types.all;
entity Exceptions is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_ena          : in     vl_logic;
        io_ocp_M_Cmd    : in     vl_logic_vector(2 downto 0);
        io_ocp_M_Addr   : in     vl_logic_vector(31 downto 0);
        io_ocp_M_Data   : in     vl_logic_vector(31 downto 0);
        io_ocp_M_ByteEn : in     vl_logic_vector(3 downto 0);
        io_ocp_S_Resp   : out    vl_logic_vector(1 downto 0);
        io_ocp_S_Data   : out    vl_logic_vector(31 downto 0);
        io_intrs_15     : in     vl_logic;
        io_intrs_14     : in     vl_logic;
        io_intrs_13     : in     vl_logic;
        io_intrs_12     : in     vl_logic;
        io_intrs_11     : in     vl_logic;
        io_intrs_10     : in     vl_logic;
        io_intrs_9      : in     vl_logic;
        io_intrs_8      : in     vl_logic;
        io_intrs_7      : in     vl_logic;
        io_intrs_6      : in     vl_logic;
        io_intrs_5      : in     vl_logic;
        io_intrs_4      : in     vl_logic;
        io_intrs_3      : in     vl_logic;
        io_intrs_2      : in     vl_logic;
        io_intrs_1      : in     vl_logic;
        io_intrs_0      : in     vl_logic;
        io_excdec_exc   : out    vl_logic;
        io_excdec_excBase: out    vl_logic_vector(29 downto 0);
        io_excdec_excAddr: out    vl_logic_vector(29 downto 0);
        io_excdec_intr  : out    vl_logic;
        io_excdec_addr  : out    vl_logic_vector(31 downto 0);
        io_excdec_src   : out    vl_logic_vector(4 downto 0);
        io_excdec_local : out    vl_logic;
        io_memexc_call  : in     vl_logic;
        io_memexc_ret   : in     vl_logic;
        io_memexc_src   : in     vl_logic_vector(4 downto 0);
        io_memexc_exc   : in     vl_logic;
        io_memexc_excBase: in     vl_logic_vector(29 downto 0);
        io_memexc_excAddr: in     vl_logic_vector(29 downto 0);
        io_superMode    : out    vl_logic;
        io_invalICache  : out    vl_logic;
        io_invalDCache  : out    vl_logic
    );
end Exceptions;
