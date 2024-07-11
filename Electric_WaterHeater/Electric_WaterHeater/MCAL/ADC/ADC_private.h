

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#ifndef Voltage_Reference_Selection
#define Voltage_Reference_Selection External_Capacitor_AREF
#endif
/*
#ifndef PRESCALER
#define PRESCALER 128
#endif
*/

#define PRESCALER_2 1
#define PRESCALER_4 2
#define PRESCALER_8 3
#define PRESCALER_16 4
#define PRESCALER_32 5
#define PRESCALER_64 6
#define PRESCALER_128 7

#define Vref_Turned_Off 0b00
#define External_Capacitor_AREF 0b01
#define Internal_REF_External_Capacitor_AREF 0b11

//        ADMUX_REG
#define REFS0 6
#define REFS1 7

//        ADCSRA_REG
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE  3 // Bit 3 � ADIE: ADC Interrupt Enable

#define ADIF 4
#define ADSC 6
#define ADEN 7

#define ADMUX_REG *((volatile u8 *)0x27)
#define ADCSRA_REG *((volatile u8 *)0x26)
#define ADC_REG *((volatile u16 *)0x24) // ADCL + ADCH

#endif /* ADC_PRIVATE_H_ */