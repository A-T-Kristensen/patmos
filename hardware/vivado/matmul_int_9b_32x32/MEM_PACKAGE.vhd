--------------------------------------------------------------------------------
-- Package for the hardware accelerators
-- this package specifies the information required for the memory banks
-- used in the currently active design (synthesis or simulation)
--
-- Author: Andreas Toftegaard Kristensen (s144026@student.dtu.dk)
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

package MEM_PACKAGE is

	-- Constants used for the memory (BRAM) between Patmos and the HwA

    -- Number of banks used by the currently active design.
    constant NBANKS  : integer := 9; 

    -- The number of entries for each the memory banks 
    --constant MEM_SIZE : integer := 1024; -- float/int: 4x4, 16x16
    --constant MEM_SIZE : integer := 2048; 
    constant MEM_SIZE : integer := 4096; -- float/int: 32x32
    --constant MEM_SIZE : integer := 8192; 

end MEM_PACKAGE;