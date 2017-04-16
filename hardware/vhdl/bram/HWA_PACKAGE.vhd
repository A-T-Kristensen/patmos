--------------------------------------------------------------------------------
-- Package for the hardware accelerators
--
-- Author: Andreas Toftegaard Kristensen
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use IEEE.math_real."ceil";
use IEEE.math_real."log2";

package HWA_PACKAGE is

	-- Constants used for the memory (bram) between Patmos and the HwA

    constant DATA_WIDTH : integer := 32; 
    constant ADDR_WIDTH    : integer := 16; -- Patmos has a 16-bit local address space
    constant NBANKS  : integer := 2; -- Number of banks (should this not be placed somewhere else?)
    constant ADDR_SELECT_BITS : integer := integer(ceil(log2(real(NBANKS)))); -- Number of bits used to select between banks from Patmos
    constant MEM_SIZE : integer := 512; -- The number of entries for each the memory banks 
    constant ADDR_INDEX : integer := integer(ceil(log2(real(MEM_SIZE)))) - 1; -- The max addr index for each bank, determined by required size.    
    constant ADDR_BITS: integer := integer(ceil(log2(real(MEM_SIZE)))); -- The actual number of address bits used
    constant BLOCK_ADDR_WIDTH : integer := integer(ADDR_WIDTH - integer(ceil(log2(real(NBANKS)))));

    type bank_master is record
        wr   : std_logic_vector(3 downto 0);
        addr : std_logic_vector(ADDR_INDEX downto 0);
        din  : std_logic_vector(DATA_WIDTH - 1 downto 0);
    end record;    

    type bank_slave is record
        dout : std_logic_vector(DATA_WIDTH - 1 downto 0);
    end record;       

    type bank_master_a is array(NBANKS-1 downto 0) of bank_master;
    type bank_slave_a is array(NBANKS-1 downto 0) of bank_slave;    

end HWA_PACKAGE;