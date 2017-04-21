library verilog;
use verilog.vl_types.all;
entity WriteBack is
    port(
        io_ena          : in     vl_logic;
        io_memwb_rd_1_addr: in     vl_logic_vector(4 downto 0);
        io_memwb_rd_1_data: in     vl_logic_vector(31 downto 0);
        io_memwb_rd_1_valid: in     vl_logic;
        io_memwb_rd_0_addr: in     vl_logic_vector(4 downto 0);
        io_memwb_rd_0_data: in     vl_logic_vector(31 downto 0);
        io_memwb_rd_0_valid: in     vl_logic;
        io_memwb_pc     : in     vl_logic_vector(29 downto 0);
        io_rfWrite_1_addr: out    vl_logic_vector(4 downto 0);
        io_rfWrite_1_data: out    vl_logic_vector(31 downto 0);
        io_rfWrite_1_valid: out    vl_logic;
        io_rfWrite_0_addr: out    vl_logic_vector(4 downto 0);
        io_rfWrite_0_data: out    vl_logic_vector(31 downto 0);
        io_rfWrite_0_valid: out    vl_logic;
        io_memResult_1_addr: out    vl_logic_vector(4 downto 0);
        io_memResult_1_data: out    vl_logic_vector(31 downto 0);
        io_memResult_1_valid: out    vl_logic;
        io_memResult_0_addr: out    vl_logic_vector(4 downto 0);
        io_memResult_0_data: out    vl_logic_vector(31 downto 0);
        io_memResult_0_valid: out    vl_logic
    );
end WriteBack;
