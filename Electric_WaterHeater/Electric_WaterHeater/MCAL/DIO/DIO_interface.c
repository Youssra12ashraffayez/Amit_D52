#include "../../LIB/STD_Type.h"
#include "../../LIB/BITMATH.h"
#include "DIO_private.h"
#include "DIO_interface.h"

void DIO_Vid_Set_Pin_Dir(u8 Copy_u8_port, u8 Copy_u8_pin, u8 Copy_u8_dir)
{
	if (Copy_u8_dir == OUTPUT || Copy_u8_dir == INPUT)
	{
		volatile u8 *dir_reg;
		switch (Copy_u8_port)
		{
			case PORTA: dir_reg = &DDRA_REG; break;
			case PORTB: dir_reg = &DDRB_REG; break;
			case PORTC: dir_reg = &DDRC_REG; break;
			case PORTD: dir_reg = &DDRD_REG; break;
			default: return;
		}

		if (Copy_u8_dir == OUTPUT)
		{
			SET_BIT(*dir_reg, Copy_u8_pin);
		}
		else
		{
			CLEAR_BIT(*dir_reg, Copy_u8_pin);
		}
	}
}

void DIO_Vid_Set_Pin_Val(u8 Copy_u8_port, u8 Copy_u8_pin, u8 Copy_u8_val)
{
	if (Copy_u8_val == HIGH || Copy_u8_val == LOW)
	{
		volatile u8 *port_reg;
		switch (Copy_u8_port)
		{
			case PORTA: port_reg = &PORTA_REG; break;
			case PORTB: port_reg = &PORTB_REG; break;
			case PORTC: port_reg = &PORTC_REG; break;
			case PORTD: port_reg = &PORTD_REG; break;
			default: return;
		}

		if (Copy_u8_val == HIGH)
		{
			SET_BIT(*port_reg, Copy_u8_pin);
		}
		else
		{
			CLEAR_BIT(*port_reg, Copy_u8_pin);
		}
	}
}

u8 DIO_u8_Get_Pin_Val(u8 Copy_u8_port, u8 Copy_u8_pin)
{
	volatile u8 *pin_reg;
	switch (Copy_u8_port)
	{
		case PORTA: pin_reg = &PINA_REG; break;
		case PORTB: pin_reg = &PINB_REG; break;
		case PORTC: pin_reg = &PINC_REG; break;
		case PORTD: pin_reg = &PIND_REG; break;
		default: return 0;
	}
	return GET_BIT(*pin_reg, Copy_u8_pin);
}

void DIO_Vid_Toggle_Pin_Val(u8 Copy_u8_port, u8 Copy_u8_pin)
{
	volatile u8 *port_reg;
	switch (Copy_u8_port)
	{
		case PORTA: port_reg = &PORTA_REG; break;
		case PORTB: port_reg = &PORTB_REG; break;
		case PORTC: port_reg = &PORTC_REG; break;
		case PORTD: port_reg = &PORTD_REG; break;
		default: return;
	}
	TOGGLE_BIT(*port_reg, Copy_u8_pin);
}

void DIO_Vid_Set_Port_Dir(u8 Copy_u8_port, u8 Copy_u8_dir)
{
	volatile u8 *dir_reg;
	switch (Copy_u8_port)
	{
		case PORTA: dir_reg = &DDRA_REG; break;
		case PORTB: dir_reg = &DDRB_REG; break;
		case PORTC: dir_reg = &DDRC_REG; break;
		case PORTD: dir_reg = &DDRD_REG; break;
		default: return;
	}
	*dir_reg = (Copy_u8_dir == PORT_OUTPUT) ? PORT_OUTPUT : PORT_INPUT;
}

void DIO_Vid_Set_Port_Val(u8 Copy_u8_port, u8 Copy_u8_val)
{
	volatile u8 *port_reg;
	switch (Copy_u8_port)
	{
		case PORTA: port_reg = &PORTA_REG; break;
		case PORTB: port_reg = &PORTB_REG; break;
		case PORTC: port_reg = &PORTC_REG; break;
		case PORTD: port_reg = &PORTD_REG; break;
		default: return;
	}
	*port_reg = Copy_u8_val;
}
