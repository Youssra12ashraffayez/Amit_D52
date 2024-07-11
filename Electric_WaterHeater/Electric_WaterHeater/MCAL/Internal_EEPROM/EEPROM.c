
#include "EEPROM_Config.h"
#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_Type.h"
#include "../Interrupts/GIE_private.h"
#include "EEPROM.h"

void EEPROM_Send(u16 copy_u16_addr, u8 copy_u16_data)
{
	u8 INT_EN = 0;

	// Setup Address Register
	EEARL_REG = (unsigned char)copy_u16_addr;
	EEARH_REG = (unsigned char)(copy_u16_addr >> 8);

	// Put Data in Data Register
	EEDR_REG = copy_u16_data;

	// Disable Interrupts
	if (((SREG_REG & (1 << 7)) >> 7) == 1)
	{
		INT_EN = 1;
		CLEAR_BIT(SREG_REG, 7);
	}

	// Start Writing
	SET_BIT(EECR_REG, EEMWE);
	SET_BIT(EECR_REG, EEWE);
	while (((EECR_REG & (1 << EEWE)) >> EEWE) == 1)
		;

	// Back
	if (INT_EN == 1)
	{
		SET_BIT(SREG_REG, 7);
	}
}

unsigned char EEPROM_Recieve(u16 copy_u16_addr)
{
	// Setup Address Register
	EEARL_REG = (unsigned char)copy_u16_addr;
	EEARH_REG = (unsigned char)(copy_u16_addr >> 8);

	// Start Reading
	SET_BIT(EECR_REG, EERE);

	// Return Data
	return EEDR_REG;
}
