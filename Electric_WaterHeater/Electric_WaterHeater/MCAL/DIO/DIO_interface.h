
#ifndef INCFILE1_H_
#define INCFILE1_H_

void DIO_Vid_Set_Pin_Dir(u8 Copy_u8_port, u8 Copy_u8_pin, u8 Copy_u8_dir);
void DIO_Vid_Set_Pin_Val(u8 Copy_u8_port, u8 Copy_u8_pin, u8 Copy_u8_val);
void DIO_Vid_Toggle_Pin_Val(u8 Copy_u8_port, u8 Copy_u8_pin);
u8 DIO_u8_Get_Pin_Val(u8 Copy_u8_port, u8 Copy_u8_pin);

void DIO_Vid_Set_Port_Dir(u8 Copy_u8_port, u8 Copy_u8_dir);
void DIO_Vid_Set_Port_Val(u8 Copy_u8_port, u8 Copy_u8_val);

/* PORT DIR */
#define PORT_OUTPUT 0xff
#define PORT_INPUT 0x00

/* PORT VAL */
#define PORT_HIGH 0xff
#define PORT_LOW 0x00

/* PIN DIR */
#define OUTPUT 1
#define INPUT 0

/* PIN Val */
#define HIGH 1
#define LOW 0

/* PORT */
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/* PINS */
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#endif /* INCFILE1_H_ */