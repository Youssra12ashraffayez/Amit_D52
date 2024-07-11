

#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

/* TCCRO PINS CONFIG */

#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0 7

/* TIMSK PINS CONFIG */

#define TOIE0 0 // Timer Counter0 Overflow Interrupt Enable
#define OCIE0 1 //  Timer Counter0 Output Compare Match Interrupt Enable

/* TIFR PINS CONFIG */

#define TOV0 0 // Timer Counter0 Overflow Flag
#define OCF0 1 //  Output Compare Flag 0

/* MODES OF TIMER  */

#define TIMER0_MODE TIMER0_NORMAL_MODE
#define TIMER0_NORMAL_MODE 0

#endif /* TIMER0_CONFIG_H_ */