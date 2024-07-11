
#include "../../LIB/STD_Type.h"
#include "../../LIB/BITMATH.h"
#include "../../LIB/Vect_table.h"
#include "../DIO/DIO_private.h"
#include "../DIO/DIO_interface.h"
#include "GIE_interface.h"

#include "EXIT_private.h"
#include "EXIT_interface.h"

/* ptr to fun*/

void (*ptr_int0)(void);
void (*ptr_int1)(void);
void (*ptr_int2)(void);

void EXT_Vid_Interrupt_Init0(u8 SENSE_CONTROL)
{

	if (SENSE_CONTROL == RISING_EDGE)
	{

		/* INT0*/
		SET_BIT(MCUCR_REG, ISC01);
		SET_BIT(MCUCR_REG, ISC00);
	}
	if (SENSE_CONTROL == FALLING_EDGE)
	{
		/* INT0*/
		SET_BIT(MCUCR_REG, ISC01);
		CLEAR_BIT(MCUCR_REG, ISC00);
	}
	if (SENSE_CONTROL == ANY_LOGIC_CHANGE)
	{
		/* INT0*/
		CLEAR_BIT(MCUCR_REG, ISC01);
		SET_BIT(MCUCR_REG, ISC00);
	}
}

void EXT_Vid_Interrupt_Init1(u8 SENSE_CONTROL)
{
	if (SENSE_CONTROL == RISING_EDGE)
	{

		/* INT1*/
		SET_BIT(MCUCR_REG, ISC11);
		SET_BIT(MCUCR_REG, ISC10);
	}
	if (SENSE_CONTROL == FALLING_EDGE)
	{
		/* INT1*/
		SET_BIT(MCUCR_REG, ISC11);
		CLEAR_BIT(MCUCR_REG, ISC10);
	}
	if (SENSE_CONTROL == ANY_LOGIC_CHANGE)
	{
		/* INT1*/
		CLEAR_BIT(MCUCR_REG, ISC11);
		SET_BIT(MCUCR_REG, ISC10);
	}
}

void EXT_Vid_Interrupt_Init2(u8 SENSE_CONTROL)
{
	if (SENSE_CONTROL == RISING_EDGE)
	{
		SET_BIT(MCUCSR_REG, ISC2);
	}

	if (SENSE_CONTROL == FALLING_EDGE)
	{
		CLEAR_BIT(MCUCSR_REG, ISC2);
	}
}

void EXT_Vid_Interrupt0()
{
	/* enable global interrupt */
	GIE_Vid_Enable();
	/*enable INT0 */
	SET_BIT(GICR_REG, INT_0_PIN);
}

void EXT_Vid_Interrupt1()
{
	GIE_Vid_Enable();
	SET_BIT(GICR_REG, INT_1_PIN);
}

void EXT_Vid_Interrupt2()
{
	GIE_Vid_Enable();
	SET_BIT(GICR_REG, INT_2_PIN);
}

void EXT_Vid_Set_CallBack(void (*ptr_set_callback)(void))
{

	ptr_int0 = ptr_set_callback;
}
void EXT_Vid_Set_CallBack_2(void (*ptr_set_callback)(void))
{
	ptr_int1 = ptr_set_callback;
}
void EXT_Vid_Set_CallBack_3(void (*ptr_set_callback)(void))
{
	ptr_int2 = ptr_set_callback;
}

ISR(INT_0)
{
	if (ptr_int0 != NULL)
	{
		ptr_int0();
	}
}

ISR(INT_1)
{
	if (ptr_int1 != NULL)
	{
		ptr_int1();
	}
}

ISR(INT_2)
{
	if (ptr_int2 != NULL)
	{
		ptr_int2();
	}
}

/* ISR0 */
/*
void  __vector_1(void)__attribute__((signal));
void __vector_1(void){


	ptr_int0() ;


}
*/