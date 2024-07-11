
#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define TCCR1A_REG *((volatile u8 *)0x4F)
#define TCCR1B_REG *((volatile u8 *)0x4E)
#define TCNT1_REG *((volatile u16 *)0x4C)
#define OCR1A_REG *((volatile u16 *)0x4A)
#define OCR1B_REG *((volatile u16 *)0x48)
#define ICR1_REG *((volatile u16 *)0x46)

#define TIMSK_REG *((volatile u8 *)0x59)
#define TIFR_REG *((volatile u8 *)0x58)

/*        TCCR1A_REG        */

#define WGM10 0
#define WGM11 1

#define COM1A1 7 // Normal _ Toggle _ Clear _ Set
#define COM1A0 6

#define COM1B1 5 // Normal  _ Toggle _ Clear _ Set (On CM)
#define COM1B0 4

/*         TCCR1B_REG        */
#define WGM12 3
#define WGM13 4

/*   Clock Select Bit Description   */
#define CS10 0
#define CS11 1
#define CS12 2

/*        TIMSK_REG        */
#define TOIE1 2  // OF interrupt enable
#define OCIE1B 3 // Compare match interrupt enable
#define OCIE1A 4 // Compare match interrupt enable
#define TICIE1 5 // Input Capture Interrupt Enable

/*        TIFR_REG        */
#define TOV1 2  //	 OF  Flag
#define OCF1B 3 //   Output Compare Flag
#define OCF1A 4 //   Output Compare Flag
#define ICF1 5  //   Input Capture Flag

#define WDTCR_Reg *((volatile u8 *)0x41)
/*   WatchDog_Timer_Reg  WDTCR */
#define WDP0 0
#define WDP1 1
#define WDP2 2
#define WDE 3
#define WDTOE 4

#endif /* TIMER1_PRIVATE_H_ */