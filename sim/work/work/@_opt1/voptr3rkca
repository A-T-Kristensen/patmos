library verilog;
use verilog.vl_types.all;
entity Queue is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_enq_ready    : out    vl_logic;
        io_enq_valid    : in     vl_logic;
        io_enq_bits     : in     vl_logic_vector(7 downto 0);
        io_deq_ready    : in     vl_logic;
        io_deq_valid    : out    vl_logic;
        io_deq_bits     : out    vl_logic_vector(7 downto 0);
        io_count        : out    vl_logic_vector(4 downto 0)
    );
end Queue;
