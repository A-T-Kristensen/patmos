--------------------------------------------------------------------------------
-- Package for the hardware accelerators
--
-- Author: Andreas Toftegaard Kristensen
--------------------------------------------------------------------------------


package HWA_PACKAGE is

	-- Constants used for the memory (bram) between Patmos and the HwA

    constant DATA_WIDTH : integer := 32;
    constant ADDR_WIDTH    : integer := 16; -- Patmos has a 16-bit local address space
    constant NBANKS  : integer := 2;
    constant BLOCK_ADDR_WIDTH : integer := integer(ADDR_WIDTH - ceil(log2(real(NBANKS))))

end HWA_PACKAGE;