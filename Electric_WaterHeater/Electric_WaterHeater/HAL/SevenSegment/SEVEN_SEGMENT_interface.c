

#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_Type.h"
#include "../../MCAL/DIO/DIO_private.h"
#include "../../MCAL/DIO/DIO_interface.h"

/*****************************************************************************
 * Function Name: SSD_Vid_Init
 * Purpose      : Initialize Seven Segment
 * Parameters   : void
 * Return value : void
 *****************************************************************************/
void SSD_Vid_Init()
{
	// Set the direction of the seven-segment display pins
	DIO_Vid_Set_Port_Dir(PORTC, PORT_OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTA, PIN1, OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTA, PIN2, OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTA, PIN3, OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB, PIN0, OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB, PIN5, OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB, PIN6, OUTPUT);
	DIO_Vid_Set_Pin_Dir(PORTB, PIN7, OUTPUT);
	// Set the direction of the control pin for the seven-segment display
	DIO_Vid_Set_Pin_Dir(PORTC, PIN7, OUTPUT);

}

/*****************************************************************************
 * Function Name: SSD_DIS
 * Purpose      : Disable Seven Segment
 * Parameters   : void
 * Return value : void
 *****************************************************************************/
void SSD_DIS()
{
	 // Disable the seven-segment display by setting the control pin to HIGH
	DIO_Vid_Set_Pin_Val(PORTC, PIN7, HIGH);
}

void SSD_EN()
{
	// Enable the seven-segment display by setting the control pin to LOW
	DIO_Vid_Set_Pin_Val(PORTC, PIN7, LOW);
}
void SSD_TOGGLE()
{
	// Toggle the state of the control pin for the seven-segment display
	DIO_Vid_Toggle_Pin_Val(PORTC, PIN7);
}

/*****************************************************************************
 * Function Name: SEVEN_SEGMENT_Write_Val
 * Purpose      : Write Value On Seven Segment
 * Parameters   : void
 * Return value : void
 *****************************************************************************/
void SEVEN_SEGMENT_Write_Val(u8 number)
{
// Array to store the segment patterns for each digit
	u8 num[10] = {0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0xFF, 0x67};
// Extract the ones and tens digits from the number
	u8 SSD1 = num[number % 10];
	u8 SSD2 = num[number / 10];

// Set the segment pins for the ones digit
	DIO_Vid_Set_Pin_Val(PORTC, PIN0, GET_BIT(SSD1, 0));
	DIO_Vid_Set_Pin_Val(PORTC, PIN1, GET_BIT(SSD1, 1));
	DIO_Vid_Set_Pin_Val(PORTC, PIN2, GET_BIT(SSD1, 2));
	DIO_Vid_Set_Pin_Val(PORTC, PIN3, GET_BIT(SSD1, 3));
	DIO_Vid_Set_Pin_Val(PORTC, PIN4, GET_BIT(SSD1, 4));
	DIO_Vid_Set_Pin_Val(PORTC, PIN5, GET_BIT(SSD1, 5));
	DIO_Vid_Set_Pin_Val(PORTC, PIN6, GET_BIT(SSD1, 6));
	
// Set the segment pins for the tens digit
	DIO_Vid_Set_Pin_Val(PORTA, PIN1, GET_BIT(SSD2, 0));
	DIO_Vid_Set_Pin_Val(PORTA, PIN2, GET_BIT(SSD2, 1));
	DIO_Vid_Set_Pin_Val(PORTA, PIN3, GET_BIT(SSD2, 2));
	DIO_Vid_Set_Pin_Val(PORTB, PIN0, GET_BIT(SSD2, 3));
	DIO_Vid_Set_Pin_Val(PORTB, PIN5, GET_BIT(SSD2, 4));
	DIO_Vid_Set_Pin_Val(PORTB, PIN6, GET_BIT(SSD2, 5));
	DIO_Vid_Set_Pin_Val(PORTB, PIN7, GET_BIT(SSD2, 6));
}