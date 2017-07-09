library verilog;
use verilog.vl_types.all;
entity MemBlock_2 is
    port(
        clk             : in     vl_logic;
        io_rdAddr       : in     vl_logic_vector(10 downto 0);
        io_rdData       : out    vl_logic_vector(7 downto 0);
        io_wrAddr       : in     vl_logic_vector(10 downto 0);
        io_wrEna        : in     vl_logic;
        io_wrData       : in     vl_logic_vector(7 downto 0)
    );
end MemBlock_2;
