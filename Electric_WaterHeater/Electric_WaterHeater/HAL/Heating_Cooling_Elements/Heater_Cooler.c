

#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_Type.h"
#include "../../MCAL/DIO/DIO_private.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "Heater_Cooler_Config.h"
#include "Heater_Cooler.h"

// Initialize heating and cooling elements pins
void Heater_Cooler_Init()
{
	DIO_Vid_Set_Pin_Dir(HEATINGELEMENTLED_PORT, HEATINGELEMENTLED_PIN, OUTPUT);
	DIO_Vid_Set_Pin_Dir(HEATINGELEMENT_PORT, HEATINGELEMENT_PIN, OUTPUT);
	DIO_Vid_Set_Pin_Dir(COOLINGELEMENT_PORT, COOLINGELEMENT_PIN, OUTPUT);
}
// Turn on the heating element LED
void Heating_ElementLed_ON()
{
	DIO_Vid_Set_Pin_Val(HEATINGELEMENTLED_PORT, HEATINGELEMENTLED_PIN, HIGH);
}
// Turn off the heating element LED
void Heating_ElementLed_OFF()
{
	DIO_Vid_Set_Pin_Val(HEATINGELEMENTLED_PORT, HEATINGELEMENTLED_PIN, LOW);
}
// Toggle the state of the heating element LED
void HeatingElement_Led_TOGGLE()
{
	DIO_Vid_Toggle_Pin_Val(HEATINGELEMENTLED_PORT, HEATINGELEMENTLED_PIN);
}
// Turn on the heating element
void HeatingElement_ON()
{
	DIO_Vid_Set_Pin_Val(HEATINGELEMENT_PORT, HEATINGELEMENT_PIN, HIGH);
}
// Turn off the heating element
void HeatingElement_OFF()
{
	DIO_Vid_Set_Pin_Val(HEATINGELEMENT_PORT, HEATINGELEMENT_PIN, LOW);
}
// Turn on the cooling element
void CoolingElement_ON()
{
	DIO_Vid_Set_Pin_Val(COOLINGELEMENT_PORT, COOLINGELEMENT_PIN, HIGH);
}
// Turn off the cooling element
void CoolingElement_OFF()
{
	DIO_Vid_Set_Pin_Val(COOLINGELEMENT_PORT, COOLINGELEMENT_PIN, LOW);
}