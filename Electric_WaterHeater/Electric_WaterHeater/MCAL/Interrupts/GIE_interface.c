
#include "../../LIB/STD_Type.h"
#include "../../LIB/BITMATH.h"

#include "GIE_private.h"

void GIE_Vid_Enable()
{

	SET_BIT(SREG_REG, 7);

	// __asm volatile("SEI") ;
}
void GIE_Vid_Disable()
{

	CLEAR_BIT(SREG_REG, 7);
	//  volatile __asm("CLI") ;
}