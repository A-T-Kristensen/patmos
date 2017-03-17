--
-- Copyright Technical University of Denmark. All rights reserved.
-- This file is part of the T-CREST project.
--
-- Redistribution and use in source and binary forms, with or without
-- modification, are permitted provided that the following conditions are met:
--
--    1. Redistributions of source code must retain the above copyright notice,
--       this list of conditions and the following disclaimer.
--
--    2. Redistributions in binary form must reproduce the above copyright
--       notice, this list of conditions and the following disclaimer in the
--       documentation and/or other materials provided with the distribution.
--
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER ``AS IS'' AND ANY EXPRESS
-- OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
-- OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
-- NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
-- DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
-- (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
-- LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
-- ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
-- (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
-- THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--
-- The views and conclusions contained in the software and documentation are
-- those of the authors and should not be interpreted as representing official
-- policies, either expressed or implied, of the copyright holder.
--


--------------------------------------------------------------------------------
-- A parameterized, memory bank using true dual-port, dual-clock block RAM.
--
-- Author: Andreas Toftegaard Kristensen
--------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity dual_bank is

generic (
    DATA    : integer := 32;
    ADDR    : integer := 16; -- ADDR bit address space from Patmos side.
    NBANKS  : integer := 2;
    ADDRSUB : integer := 2 -- log[2](NBANKS) + 1. 
    );

port (
    clk     : in  std_logic;
    -- Patmos side

    p_we    : in  std_logic;
    p_addr  : in  std_logic_vector(ADDR - 1 downto 0); -- The upper bits are used to select bank.
    p_dout  : in  std_logic_vector(DATA - 1 downto 0);
    p_din   : out std_logic_vector(DATA - 1 downto 0);    -- Input to patmos

    -- HLS Side

 -- Bank 1
    b1_wr    : in  std_logic;
    b1_addr  : in  std_logic_vector(ADDR - ADDRSUB downto 0);
    b1_din   : in  std_logic_vector(DATA - 1 downto 0);
    b1_dout  : out std_logic_vector(DATA - 1 downto 0);

-- Bank 2
    b2_wr    : in  std_logic;
    b2_addr  : in  std_logic_vector(ADDR - ADDRSUB downto 0);
    b2_din   : in  std_logic_vector(DATA - 1 downto 0);
    b2_dout  : out std_logic_vector(DATA - 1 downto 0)            
);
end dual_bank;

architecture rtl of dual_bank is
    
    component bram_tdp is
        port (
            -- Port A
            a_clk   : in  std_logic;
            a_wr    : in  std_logic;
            a_addr  : in  std_logic_vector(ADDR - ADDRSUB downto 0);
            a_din   : in  std_logic_vector(DATA - 1 downto 0);
            a_dout  : out std_logic_vector(DATA - 1 downto 0);

            -- Port B
            b_clk   : in  std_logic;
            b_wr    : in  std_logic;
            b_addr  : in  std_logic_vector(ADDR - ADDRSUB downto 0);
            b_din   : in  std_logic_vector(DATA - 1 downto 0);
            b_dout  : out  std_logic_vector(DATA - 1 downto 0)
        );
    end component;  

    -- Bank control signals

    signal p_b1_we, p_b2_we : std_logic;  -- Write enable from patmos to bank i    
    signal p_bank_sel : std_logic := '0';  -- memory bank select signal
    signal p_b1_data, p_b2_data : std_logic_vector(DATA-1 downto 0); -- output data from bank i to patmos

begin 

    bram_tdp_inst_0 : bram_tdp port map(
        -- Port A
        a_clk   => clk,
        a_wr    => p_b1_we,
        a_addr  => p_addr(ADDR - ADDRSUB downto 0),
        a_din   => p_dout,
        a_dout  => p_b1_data,
        
        -- Port B
        b_clk   => clk,
        b_wr    => b1_wr,
        b_addr  => b1_addr,
        b_din   => b1_din,
        b_dout  => b1_dout
    );

    bram_tdp_inst_1 : bram_tdp port map(
        -- Port A
        a_clk   => clk,
        a_wr    => p_b2_we,
        a_addr  => p_addr(ADDR - ADDRSUB downto 0),
        a_din   => p_dout,
        a_dout  => p_b2_data,
        
        -- Port B
        b_clk   => clk,
        b_wr    => b2_wr,
        b_addr  => b2_addr,
        b_din   => b2_din,
        b_dout  => b2_dout
    );
    
    -- Select data for output port on patmos side
    -- use MSB bits
    p_bank_sel <= p_addr(ADDR - 1);

    outputSelect : process(p_bank_sel, p_b1_data, p_b2_data) is
    begin
        if(p_bank_sel = '0') then
            p_din <= p_b1_data;
        elsif (p_bank_sel = '1') then
            p_din <= p_b2_data;
        else
            p_din <= (others => '0');
        end if;
    end process;

    writeSelect : process(p_bank_sel, p_we) is
    begin
        if(p_bank_sel = '0' and p_we = '1') then
            p_b1_we <= '1';
            p_b2_we <= '0';
        elsif (p_bank_sel = '1' and p_we = '1') then
            p_b1_we <= '0';
            p_b2_we <= '1';
        else
            p_b1_we <= '0';
            p_b2_we <= '0';
        end if;
    end process;

end rtl;

