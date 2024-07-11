#ifndef VECT_TABLE_H_
#define VECT_TABLE_H_

#define ISR(__vector_num)                            \
	void __vector_num(void) __attribute__((signal)); \
	void __vector_num(void)

#define INT_0 __vector_1
#define INT_1 __vector_2
#define INT_2 __vector_3
#define TIMER0_COMP __vector_10
#define TIMER0_OF __vector_11
#define ADC_INT __vector_16
#define TIMER1_CAPT __vector_6
#define TIMER1_COMPA __vector_7
#define TIMER1_OVF __vector_9

#endif