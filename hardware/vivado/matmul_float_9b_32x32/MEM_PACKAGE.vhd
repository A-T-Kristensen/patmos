--------------------------------------------------------------------------------
-- Package for the hardware accelerators
-- this package specifies the information required for the memory banks
-- used locally
--
-- Author: Andreas Toftegaard Kristensen (s144026@student.dtu.dk)
--------------------------------------------------------------------------------

package MEM_PACKAGE is

	-- Constants used for the memory (BRAM) between Patmos and the HwA

    -- Number of banks used by the currently active design.
    constant NBANKS  : integer := 9; 

    -- The number of entries for each the memory banks 
    constant MEM_SIZE : integer := 4096;

end package;