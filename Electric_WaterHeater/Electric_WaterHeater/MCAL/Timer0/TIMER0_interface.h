

#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

#define Timer_mode Normal_mode

#define Normal_mode 0
#define CTC_mode 1
#define PWM_mode 2

// the enable of the timer is the prescaler being chosen

void TIMER0_Vid_Start(u8 prescaler);

void TIMER0_Vid_Stop();

void TIMER0_DELAY_ms(u32 Delay_ms);

void TIMER0_DELAY_us(u32 Delay_us);

void TIMER0_Vid_Interrupt_Enable();

void TIMER0_Vid_Interrupt_Enable_Every(u32 Delay_ms);

void TIMER0_Vid_CTC_Interrupt_Enable();

u32 TIMER0_Vid_Delay_CTC(u32 Delay_ms);

// TIMER0_Vid_SetCallBack(CTC_mode,LED_TOGGLE);

void TIMER0_Vid_Polling();

void Timer0_Fast_PWM(u8 duty_cycle);

void TIMER0_Vid_Set_CallBack(void (*ptr_set_callback)(void));

#define Timer_Stop 0
#define No_prescaling 1
#define _8_prescaling 2
#define _64_prescaling 3
#define _256_prescaling 4
#define _1024_prescaling 5

#endif /* TIMER0_INTERFACE_H_ */