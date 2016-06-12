----------------------------------------------------------------------------------
-- Company: Факултет инжењерских наука
-- Engineer: Никола Бабић
-- 
-- Create Date:    00:54:38 06/09/2016 
-- Design Name: Морзеова азбука
-- Module Name:    morseova_azbuka - Behavioral 
-- Project Name: Морзеова азубка
-- Target Devices: Nexys 2
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;


entity morzeova_azbuka is
port
    (
        RESET: in std_logic; 
        CLK : in std_logic;
		  LED : out std_logic 
    );
end morzeova_azbuka;

architecture Behavioral of morzeova_azbuka is

signal VREME : std_logic_vector (23 downto 0) := (others => '0'); --26 downto 0 za period od jedne sekunde
signal BROJAC : integer range 0 to 55500;

begin

process(CLK)
begin

if rising_edge(CLK) then
    if(VREME = b"101111101011110000100000") then --za period od jedne sekunde 10111110101111000010000000
        BROJAC <= BROJAC + 1; 
        VREME <= (others => '0');
    else
		  VREME <= VREME + 1;
    end if;

    if( RESET = '1' ) then
		  BROJAC <= 0;
		  LED <= '0';
    end if;

    -----------------
if( BROJAC >= 0 AND BROJAC < 3) then
		 LED <= '1';
end if;

if( BROJAC >= 3 AND BROJAC < 4) then
		 LED <= '0';
end if;

if( BROJAC >= 4 AND BROJAC < 7) then
		 LED <= '1';
end if;

if( BROJAC >= 7 AND BROJAC < 8) then
		 LED <= '0';
end if;

if( BROJAC >= 8 AND BROJAC < 11) then
		 LED <= '1';
end if;

if( BROJAC >= 11 AND BROJAC < 14) then
		 LED <= '0';
end if;

if( BROJAC >= 14 AND BROJAC < 15) then
		 LED <= '1';
end if;

if( BROJAC >= 15 AND BROJAC < 16) then
		 LED <= '0';
end if;

if( BROJAC >= 16 AND BROJAC < 19) then
		 LED <= '1';
end if;

if( BROJAC >= 19 AND BROJAC < 20) then
		 LED <= '0';
end if;

if( BROJAC >= 20 AND BROJAC < 21) then
		 LED <= '1';
end if;

if( BROJAC >= 21 AND BROJAC < 24) then
		 LED <= '0';
end if;

if( BROJAC >= 24 AND BROJAC < 27) then
		 LED <= '1';
end if;

if( BROJAC >= 27 AND BROJAC < 30) then
		 LED <= '0';
end if;

if( BROJAC > 40 ) then
		 BROJAC <= 0;
end if;


    ------------------

end if;
end process;
end Behavioral;
