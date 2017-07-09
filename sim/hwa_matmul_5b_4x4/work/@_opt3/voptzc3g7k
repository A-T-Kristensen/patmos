library verilog;
use verilog.vl_types.all;
entity MCacheCtrl is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        io_ena_in       : in     vl_logic;
        io_fetchEna     : out    vl_logic;
        io_ctrlrepl_wEna: out    vl_logic;
        io_ctrlrepl_wData: out    vl_logic_vector(31 downto 0);
        io_ctrlrepl_wAddr: out    vl_logic_vector(31 downto 0);
        io_ctrlrepl_wTag: out    vl_logic;
        io_ctrlrepl_addrEven: out    vl_logic_vector(9 downto 0);
        io_ctrlrepl_addrOdd: out    vl_logic_vector(9 downto 0);
        io_ctrlrepl_instrStall: out    vl_logic;
        io_replctrl_hit : in     vl_logic;
        io_femcache_addrEven: in     vl_logic_vector(31 downto 0);
        io_femcache_addrOdd: in     vl_logic_vector(31 downto 0);
        io_exmcache_doCallRet: in     vl_logic;
        io_exmcache_callRetBase: in     vl_logic_vector(31 downto 0);
        io_exmcache_callRetAddr: in     vl_logic_vector(31 downto 0);
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
        io_forceHit     : out    vl_logic
    );
end MCacheCtrl;
