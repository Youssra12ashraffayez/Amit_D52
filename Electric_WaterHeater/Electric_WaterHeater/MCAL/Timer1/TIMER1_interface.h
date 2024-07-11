

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

void TIMER1_Vid_Start(u8 prescaler);
void Timer1_OF_SetCallBack(void (*ptr)(void));
void TIMER1_Vid_Interrupt_Enable_Every(u32 Delay_ms);
void TIMER1_Vid_Stop();
void TIMER1_Vid_CTC_Init();
void TIMER1_Vid_CTC_InterruptEnable();
void Timer1_CTC_SetCallBack(void (*ptr)(void));
#define Timer_Stop 0
#define No_prescaling 1
#define _8_prescaling 2
#define _64_prescaling 3
#define _256_prescaling 4
#define _1024_prescaling 5

#endif /* TIMER1_INTERFACE_H_ */