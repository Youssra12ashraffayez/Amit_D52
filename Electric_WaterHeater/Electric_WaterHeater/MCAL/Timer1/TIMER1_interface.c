#include "../../LIB/STD_Type.h"
#include "../../LIB/BITMATH.h"
#include "../../LIB/Vect_table.h"
#include "../Interrupts/GIE_interface.h"
#include "../Interrupts/EXIT_interface.h"
#include "../../LIB/Vect_table.h"
#include "TIMER1_private.h"
#include "TIMER1_interface.h"

u32 OF1_Count = 0;
u16 T1_Prescaler[] = {0, 1, 8, 64, 256, 1024};
void (*ptr_OF)(void);
void (*ptr_CV)(void) = 0;

void TIMER1_Vid_Start(u8 prescaler)
{

	TCCR1B_REG &= 0b11111000;

	CLEAR_BIT(TCCR1A_REG, WGM10);
	CLEAR_BIT(TCCR1A_REG, WGM11);

	CLEAR_BIT(TCCR1B_REG, WGM12);
	CLEAR_BIT(TCCR1B_REG, WGM13);

	TCCR1B_REG |= prescaler;
}

void TIMER1_Vid_Interrupt_Enable_Every(u32 Delay_ms)
{
	/* Enable global interrupt */
	GIE_Vid_Enable();

	/* Enable timer interrupt (PIE) */
	SET_BIT(TIMSK_REG, TOIE1);

	u8 prescaler = _64_prescaling;
	OF1_Count = 0;

	OF1_Count = Delay_ms / ((T1_Prescaler[prescaler] * 65536.0) / 16000); // Desired(ms) / overflow time(ms)

	TIMER1_Vid_Start(prescaler);
}

void TIMER1_Vid_CTC_Init()
{
	// Select CTC Mode
	SET_BIT(TCCR1B_REG, WGM12);
	// Load Value in OCR1A
	OCR1A_REG = 62500; // For 1 sec, OCR1A_REG= Time * 16Mhz / prescaler = 1 * 16M / 256
	TIMER1_Vid_Start(_256_prescaling);
	GIE_Vid_Enable();
}

void TIMER1_Vid_CTC_InterruptEnable()
{
	SET_BIT(TIMSK_REG, OCIE1A);
}

void Timer1_CTC_SetCallBack(void (*ptr)(void))
{
	ptr_CV = ptr;
}

ISR(TIMER1_COMPA)
{
	ptr_CV();
}

void Timer1_OF_SetCallBack(void (*ptr)(void))
{
	ptr_OF = ptr;
}

ISR(TIMER1_OVF)
{

	ptr_OF();
}

void TIMER1_Vid_Stop()
{
	TCCR1B_REG = 0x00;
}