library verilog;
use verilog.vl_types.all;
entity RegisterFile is
    port(
        clk             : in     vl_logic;
        io_ena          : in     vl_logic;
        io_rfRead_rsAddr_3: in     vl_logic_vector(4 downto 0);
        io_rfRead_rsAddr_2: in     vl_logic_vector(4 downto 0);
        io_rfRead_rsAddr_1: in     vl_logic_vector(4 downto 0);
        io_rfRead_rsAddr_0: in     vl_logic_vector(4 downto 0);
        io_rfRead_rsData_3: out    vl_logic_vector(31 downto 0);
        io_rfRead_rsData_2: out    vl_logic_vector(31 downto 0);
        io_rfRead_rsData_1: out    vl_logic_vector(31 downto 0);
        io_rfRead_rsData_0: out    vl_logic_vector(31 downto 0);
        io_rfWrite_1_addr: in     vl_logic_vector(4 downto 0);
        io_rfWrite_1_data: in     vl_logic_vector(31 downto 0);
        io_rfWrite_1_valid: in     vl_logic;
        io_rfWrite_0_addr: in     vl_logic_vector(4 downto 0);
        io_rfWrite_0_data: in     vl_logic_vector(31 downto 0);
        io_rfWrite_0_valid: in     vl_logic
    );
end RegisterFile;
