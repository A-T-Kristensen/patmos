library verilog;
use verilog.vl_types.all;
entity Spm is
    port(
        clk             : in     vl_logic;
        io_M_Cmd        : in     vl_logic_vector(2 downto 0);
        io_M_Addr       : in     vl_logic_vector(12 downto 0);
        io_M_Data       : in     vl_logic_vector(31 downto 0);
        io_M_ByteEn     : in     vl_logic_vector(3 downto 0);
        io_S_Resp       : out    vl_logic_vector(1 downto 0);
        io_S_Data       : out    vl_logic_vector(31 downto 0)
    );
end Spm;
