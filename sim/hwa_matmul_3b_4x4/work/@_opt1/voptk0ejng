library verilog;
use verilog.vl_types.all;
entity MCacheMem is
    port(
        clk             : in     vl_logic;
        io_memIn_wEven  : in     vl_logic;
        io_memIn_wOdd   : in     vl_logic;
        io_memIn_wData  : in     vl_logic_vector(31 downto 0);
        io_memIn_wAddr  : in     vl_logic_vector(8 downto 0);
        io_memIn_addrEven: in     vl_logic_vector(8 downto 0);
        io_memIn_addrOdd: in     vl_logic_vector(8 downto 0);
        io_memOut_instrEven: out    vl_logic_vector(31 downto 0);
        io_memOut_instrOdd: out    vl_logic_vector(31 downto 0)
    );
end MCacheMem;
