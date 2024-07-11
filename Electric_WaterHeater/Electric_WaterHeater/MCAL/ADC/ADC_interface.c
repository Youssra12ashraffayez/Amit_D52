
#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_Type.h"
#include "../../LIB/Vect_table.h"
#include "ADC_private.h"
#include "../Interrupts/GIE_interface.h"

void (*ptr1)(void);

void ADC_Vid_Init(void)
{

	/* Select prescaler ---> 128  */

	ADCSRA_REG &= 0b11111000;
	ADCSRA_REG |= PRESCALER_128;

	/*  select AVCC  */

#if Voltage_Reference_Selection == Internal_Vref_Turned_off

	CLEAR_BIT(ADMUX, REFS0);
	CLEAR_BIT(ADMUX, REFS1);

#elif Voltage_Reference_Selection == AVCC_with_external_capacitor_at_AREF_pin

	SET_BIT(ADMUX, REFS0);
	CLEAR_BIT(ADMUX, REFS1);

#elif Voltage_Reference_Selection == Internal_externalcapacitor_AREF

	SET_BIT(ADMUX, REFS0);
	SET_BIT(ADMUX, REFS1);

#endif

	/*  ENABLE ADC */

	SET_BIT(ADCSRA_REG, ADEN);
}

u16 ADC_u16_Read()
{

	// SET_BIT(ADCSRA_REG,ADSC) ;  // START conversion

	// Polling
	// while(GET_BIT(ADCSRA_REG,ADIF)==0) ;
	//  clr flag by writing 1
	// SET_BIT(ADCSRA_REG,ADIF) ;

	return ADC_REG;
}

void ADC_Vid_Start_Conversion(u8 copy_u8_ch)
{
	ADMUX_REG &= 0b11100000; // Select Channel

	ADMUX_REG |= copy_u8_ch; // Select Channel

	SET_BIT(ADCSRA_REG, ADSC); // START conversion
}

void ADC_Vid_Interrupt_Enable()
{
	/* enable global interrupt */
	GIE_Vid_Enable();
	/*enable INT */
	SET_BIT(ADCSRA_REG, ADIE);
}

void ADC_Vid_Interrupt_Disable()
{
	/* enable global interrupt */
	GIE_Vid_Disable();
	/*enable INT */
	CLEAR_BIT(ADCSRA_REG, ADIE);
}

/* ISR ADC INT*/
ISR(ADC_INT)
{

	ptr1();
}

void ADC_Set_Call_Back(void (*ptr0)(void))
{
	ptr1 = ptr0;
}
