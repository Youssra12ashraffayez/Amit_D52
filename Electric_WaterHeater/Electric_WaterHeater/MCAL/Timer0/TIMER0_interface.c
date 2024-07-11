

#include "../../LIB/STD_Type.h"
#include "../../LIB/BITMATH.h"
#include "../../LIB/Vect_table.h"
#include "../Interrupts/GIE_interface.h"
#include "TIMER0_Config.h"
#include "TIMER0_private.h"
#include "TIMER0_interface.h"
#include "../ADC/ADC_interface.h"

void (*ptr_TIMER0_int)(void);

u16 AR_Prescaler[] = {0, 1, 8, 64, 256, 1024};

u32 OF_Count = 0;

void TIMER0_Vid_Start(u8 prescaler)
{

	TCCR0_REG &= 0b11111000;

#if Timer_mode == Normal_mode

	CLEAR_BIT(TCCR0_REG, WGM01);
	CLEAR_BIT(TCCR0_REG, WGM00);

#endif

#if Timer_mode == CTC_mode

	SET_BIT(TCCR0_REG, WGM01);
	CLEAR_BIT(TCCR0_REG, WGM00);

	CLEAR_BIT(TCCR0_REG, COM01);
	SET_BIT(TCCR0_REG, COM00);

#endif

#if Timer_mode == PWM_mode

	CLEAR_BIT(TCCR0_REG, WGM01);
	SET_BIT(TCCR0_REG, WGM00);

	SET_BIT(TCCR0_REG, COM01);
	CLEAR_BIT(TCCR0_REG, COM00);

#endif

	TCCR0_REG |= prescaler;
}

void TIMER0_Vid_Polling()
{

	while (GET_BIT(TIFR_REG, TOV0) == 0)
		;
	SET_BIT(TIFR_REG, TOV0); // clear flag by setting to 1
	TIMER0_Vid_Stop();
}

void TIMER0_Vid_Stop()
{
	TCCR0_REG = 0x00;
}

void TIMER0_DELAY_ms(u32 Delay_ms)
{
	u8 prescaler = _8_prescaling;
	u32 Count = 0;
	u32 OF_Count = 0;

	// how many overflows do i want to reach the overflow count
	OF_Count = Delay_ms / ((AR_Prescaler[prescaler] * 256.0) / 16000); // Desired(ms) / overflow time(ms)           // overflow time = tick time * overflow count(256)

	// OF_Count  = Delay_ms/0.016 ;  // if delay = 10 & prescaler = 1 then --> 625  OF_Count
	// OF_Count  = Delay_ms/1.024 ;  // if delay = 10 & prescaler = 64 then --> 9.76   OF_Count

	while (Count < OF_Count)
	{
		Count++;
		TIMER0_Vid_Start(prescaler);
		TIMER0_Vid_Polling();
	}
}

void TIMER0_DELAY_us(u32 Delay_us)
{
	while (Delay_us--)
	{
		TIMER0_Vid_Start(1);
	}
}

void TIMER0_Vid_Interrupt_Enable()
{
	/* Enable global interrupt */
	GIE_Vid_Enable();

	/* Enable timer interrupt (PIE) */
	SET_BIT(TIMSK_REG, TOIE);
}

void TIMER0_Vid_Interrupt_Enable_Every(u32 Delay_ms)
{
	/* Enable global interrupt */
	GIE_Vid_Enable();

	/* Enable timer interrupt (PIE) */
	SET_BIT(TIMSK_REG, TOIE);

	u8 prescaler = _64_prescaling;

	OF_Count = Delay_ms / ((AR_Prescaler[prescaler] * 256.0) / 16000); // Desired(ms) / overflow time(ms)

	TIMER0_Vid_Start(prescaler);
}

void TIMER0_Vid_CTC_Interrupt_Enable()
{
	/* Enable global interrupt */
	GIE_Vid_Enable();

	/* Enable timer interrupt (PIE) */
	SET_BIT(TIMSK_REG, OCIE0);
}

u32 TIMER0_Vid_Delay_CTC(u32 Delay_ms)
{

	u8 prescaler = _64_prescaling;
	u32 OF_Count = 0;
	u32 CTC_OF = 100;

	OF_Count = Delay_ms / ((AR_Prescaler[prescaler] * CTC_OF) / 16000); // Desired(ms) / overflow time(ms)

	OCR_REG = CTC_OF;

	TIMER0_Vid_Start(prescaler);

	return OF_Count;
}

void Timer0_Fast_PWM(u8 duty_cycle)
{
	u8 prescaler = _64_prescaling;
	u32 CTC_OF = (u32)duty_cycle * 256 / 100;
	OCR_REG = CTC_OF;
	TIMER0_Vid_Start(prescaler);

	while (GET_BIT(TIFR_REG, OCF0) == 0)
		;
	SET_BIT(TIFR_REG, OCF0);
}

void TIMER0_Vid_Set_CallBack(void (*ptr_set_callback)(void))
{
	ptr_TIMER0_int = ptr_set_callback;
}

ISR(TIMER0_OF)
{

	if (ptr_TIMER0_int != NULL)
	{
		ptr_TIMER0_int();
	}
}