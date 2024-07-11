

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_Vid_Init(void);

u16 ADC_u16_Read();

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

void ADC_Vid_Interrupt_Enable();
void ADC_Vid_Interrupt_Disable();
void ADC_Set_Call_Back(void (*ptr0)(void));
void ADC_Vid_Start_Conversion(u8 copy_u8_ch);

/*
#ifdef LCD_INTERFACE_H_
// define a global variable as u16 ADC_Prev_Read in main
void LCD_Vid_Send_ADC(u16 Copy_u16_Read , u16 Copy_u16_Prev_Read);
#endif
*/

#endif /* ADC_INTERFACE_H_ */