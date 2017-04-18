
--------------------------------------------------------------------------------
-- A parameterized, memory bank using true dual-port, dual-clock block RAM.
--
-- Author: Andreas Toftegaard Kristensen
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use IEEE.math_real."ceil";
use IEEE.math_real."log2";
use work.HWA_PACKAGE.all;

entity n_bank is
	port (
	    clk     : in  std_logic;

	    -- Patmos side this is always the same
	    p_we    : in  std_logic;
	    p_addr  : in  std_logic_vector(ADDR_WIDTH - 1 downto 0); -- The upper bits are used to select bank.
	    p_dout  : in  std_logic_vector(DATA_WIDTH - 1 downto 0);
	    p_din   : out std_logic_vector(DATA_WIDTH - 1 downto 0);    -- Input to patmos

	    -- HwA HLS Side, this is parametized
        bram_m : in bank_master_a;
        bram_s : out bank_slave_a       
	);
end n_bank;

architecture rtl of n_bank is
    
    component bram_tdp is
    	generic (
    		DATA: integer := DATA_WIDTH;
    		ADDR: integer := ADDR_BITS
    		);
        port (
            -- Port A (Patmos side)
            a_clk   : in  std_logic;
            a_wr    : in  std_logic;
            a_addr  : in  std_logic_vector(ADDR_BITS - 1 downto 0); -- The MSB will be used to select bram block
            a_din   : in  std_logic_vector(DATA_WIDTH - 1 downto 0);
            a_dout  : out std_logic_vector(DATA_WIDTH - 1 downto 0);

            -- Port B (HwA side)
            b_clk   : in  std_logic;
            b_wr    : in  std_logic;
            b_addr  : in  std_logic_vector(ADDR_BITS - 1 downto 0);
            b_din   : in  std_logic_vector(DATA_WIDTH - 1 downto 0);
            b_dout  : out std_logic_vector(DATA_WIDTH - 1 downto 0)
        );
    end component;  

    -- Bank control signals

	-- Write enable from patmos to bank i  
	-- index as std_logic
    signal p_b_we : std_logic_vector(NBANKS - 1 downto 0) := (others => '0');  
    								 
     -- memory bank select signal
     -- index as std_logic
    signal p_bank_sel, p_bank_sel_next : std_logic_vector(ADDR_SELECT_BITS - 1 downto 0) := (others => '0'); 
    														
 	-- output data from bank i to patmos 
    signal p_b_data : bank_slave_a;

    signal bram_m_i : bank_master_a;
    signal bram_s_i: bank_slave_a;
    									
begin 

	-- Generate memory banks

	bram_gen:
	for i in (NBANKS-1) downto 0 generate
		bram_array: bram_tdp
			port map(
	        -- Port A
	        a_clk   => clk,
	        a_wr    => p_b_we(i),
	        a_addr  => p_addr(ADDR_BITS - 1 downto 0), 
	        a_din   => p_dout,
	        a_dout  => p_b_data(i).dout,
	        
	        -- Port B
	        b_clk   => clk,
            b_wr    => bram_m_i(i).wr(0),
            b_addr  => bram_m_i(i).addr,
            b_din   => bram_m_i(i).din,
            b_dout  => bram_s_i(i).dout
	    );
	end generate;
    
    -- Select data for output port on patmos side
    -- use MSB bits
    p_bank_sel_next <= p_addr(ADDR_WIDTH - 1 downto ADDR_WIDTH - ADDR_SELECT_BITS);


    -- The bank select for output reads for patmos, these are delayed a cycle
    -- since it is for reads from the bram
    process (clk)
    begin
        if rising_edge(clk) then
            p_bank_sel <= p_bank_sel_next;
        else
            p_bank_sel <= p_bank_sel;
        end if;
    end process;

    --outputSelect : process(p_bank_sel, p_b_data)
    --begin
    --    if (to_integer(unsigned(p_bank_sel)) = 0) then
    --            p_din <= p_b_data(0).dout;
    --    elsif (to_integer(unsigned(p_bank_sel)) = 1) then
    --            p_din <= p_b_data(1).dout;
    --    else 
    --            p_din <= (others => '0');
    --    end if;
    --end process;   

    outputSelect : process(p_bank_sel, p_b_data)
    begin
    	p_din <= (others => '0');
    	for i in 0 to (NBANKS-1) loop
    		if (to_integer(unsigned(p_bank_sel)) = i) then
    			p_din <= p_b_data(i).dout;
        	end if;
        end loop;
    end process;      

    -- Combinational logic for controlling the write enable on each memory bank
    -- from the Patmos CPU
    we_gen:
	for i in (NBANKS-1) downto 0 generate
	    	p_b_we(i) <= '1' when 
	    		(p_we = '1' and to_integer(unsigned(p_bank_sel_next)) = i) 
	    		else '0';
	    end generate;

    bram_m_i <=  bram_m;
    bram_s <= bram_s_i;        

end rtl;

