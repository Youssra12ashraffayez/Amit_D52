

#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

#define TCCR0_REG *((volatile u8 *)0x53)
#define TCNT0_REG *((volatile u8 *)0x52)
#define OCR_REG *((volatile u8 *)0x5C)
#define TIMSK_REG *((volatile u8 *)0x59)
#define TIFR_REG *((volatile u8 *)0x58)

/*        TCCR0_REG        */

#define WGM00 6
#define WGM01 3

#define COM01 5
#define COM00 4

/*        TCNT0_REG        */

/*        OCR_REG        */

/*        TIMSK_REG        */
#define TOIE 0  // OF interrupt enable
#define OCIE0 1 // Compare match interrupt enable

/*        TIFR_REG        */

#define TOV0 0 //	OF  Flag
#define OCF0 1 //   Output Compare Flag

#endif /* TIMER0_PRIVATE_H_ */