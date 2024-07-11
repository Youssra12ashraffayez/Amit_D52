
#include "../LIB/BITMATH.h"
#include "../LIB/STD_Type.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/Interrupts/GIE_interface.h"
#include "../MCAL/Interrupts/EXIT_interface.h"
#include "../MCAL/Internal_EEPROM/EEPROM.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/TIMER1/TIMER1_interface.h"

#include "../HAL/SevenSegment/SEVEN_SEGMENT_interface.h"
#include "../HAL/Heating_Cooling_Elements/Heater_Cooler_Config.h"
#include "../HAL/Heating_Cooling_Elements/Heater_Cooler.h"

#include "System_Config.h"
#include "System.h"

#define F_CPU 16000000UL
#include "util/delay.h"

/* Global Variables to be used in our system */

u8 SettingMode_Flag = 0;
u8 counter_5sec = 0;
u8 counter_up = 0;
u8 counter_down = 0;

// Initializing EEPROM with temperature = 60 if no temperature is stored yet
void EEPROM_Init()
{
	u8 Loc_Var = EEPROM_Recieve(0);
	// Check if EEPROM has been initialized
	if (Loc_Var == 0)
	{
		// If not initialized, set default temperature and store it in EEPROM
		EEPROM_Send(0, Temp_Set);
	}
}

void System_Init()
{

	/*Global Interrupt */
	GIE_Vid_Enable();

	/* External Interrupt 0 for increasing temperature setting */
	EXT_Vid_Interrupt_Init0(RISING_EDGE);
	EXT_Vid_Interrupt0();
	EXT_Vid_Set_CallBack(Temperature_Setting_Up);

	 /* External Interrupt 1 for decreasing temperature setting */
	EXT_Vid_Interrupt_Init1(RISING_EDGE);
	EXT_Vid_Interrupt1();
	EXT_Vid_Set_CallBack_2(Temperature_Setting_Down);

	/*External Interrupt 2 for Switching ON/OFF System */
	EXT_Vid_Interrupt_Init2(RISING_EDGE);
	EXT_Vid_Interrupt2();
	EXT_Vid_Set_CallBack_3(ON_OFF_Behaviour);

	/* Set pin directions for buttons */
	DIO_Vid_Set_Pin_Dir(UP_BUTTON_PORT, UP_BUTTON_PIN, INPUT);
	DIO_Vid_Set_Pin_Dir(DOWN_BUTTON_PORT, DOWN_BUTTON_PIN, INPUT);
	DIO_Vid_Set_Pin_Dir(ON_OFF_PORT, ON_OFF_PIN, INPUT);
	// Initialize heating and cooling elements
	Heater_Cooler_Init();

	/*Seven Segment Initialization */
	SSD_Vid_Init();

	/* ADC Initialization */
	ADC_Vid_Init();
    /* ADC Interrupt Enable */
	ADC_Vid_Interrupt_Enable();
	ADC_Set_Call_Back(Temperature_Sensing);

	/* Timer0 Normal */
	TIMER0_Vid_Interrupt_Enable_Every(100); // 100 ms
	TIMER0_Vid_Set_CallBack(ADC_Reading_Timer);

	/*Timer 1 CTC*/
	TIMER1_Vid_CTC_Init();
	TIMER1_Vid_CTC_InterruptEnable();
	Timer1_CTC_SetCallBack(TemperatureMonitoringTask);
}

void ADC_Reading_Timer()
{
	static u16 counter1 = 0;
	counter1++;
	// Check if the timer has reached the overflow count (100 ms)
	if (counter1 == OF_Count) // 100 ms
	{
		counter1 = 0;
		ADC_Vid_Start_Conversion(ADC0);
	}
}

void Temperature_Setting_Up()
{
	if (counter_up != 0 && System_Mode == SYSTEM_ON)
	{
		counter_5sec = 0;
		Temp_Set = (Temp_Set + 5 <= 75) ? Temp_Set + 5 : 75;
		EEPROM_Send(0, Temp_Set);
	}
	else
	{
		counter_up++;
		counter_5sec = 0;
	}
}

void Temperature_Setting_Down()
{
	if (counter_down != 0 && System_Mode == SYSTEM_ON)
	{
		counter_5sec = 0;
		Temp_Set = (Temp_Set - 5 >= 35) ? Temp_Set - 5 : 35;
		EEPROM_Send(0, Temp_Set);
	}
	else
	{
		counter_down++;
		counter_5sec = 0;
	}
}


void ON_OFF_Behaviour()
{
 // Check if the system is currently OFF
	if (System_Mode == SYSTEM_OFF)
	{
// Retrieve last saved temperature setting from EEPROM
		Temp_Set = EEPROM_Recieve(0);
		// Set system state to ON
		System_Mode = SYSTEM_ON;
	}
	else
	{
	// Turn off display and all heating/cooling elements
		SSD_DIS();
		Heating_ElementLed_OFF();
		CoolingElement_OFF();
		HeatingElement_OFF();
		// Save current temperature setting to EEPROM
		EEPROM_Send(0, Temp_Set);
		// Set system state to OFF
		System_Mode = SYSTEM_OFF;
	}
}

void Temperature_Sensing()
{
	static u8 counter2 = 0;
	static u16 Temp_Sum = 0;
	if (System_Mode == SYSTEM_ON)
	{
		counter2++;
		 // Read current temperature from ADC
		Temp_Curr = ADC_u16_Read() * (float)500 / 1024;
		Temp_Sum += Temp_Curr;
	// Average temperature over 10 readings
		if (counter2 == 10)
		{
			counter2 = 0;
			Temp_AVG = Temp_Sum / 10;
			Temp_Sum = 0;
			// Control heating/cooling elements based on temperature
			Heater_Cooler_Control();
		}
	}
}

void Heater_Cooler_Control()
{
	// Required Temperature is equal to room temperature, so no action needed
	if( ( Temp_Set<Temp_AVG+TEMP_MARGIN ) && (Temp_Set>Temp_AVG-TEMP_MARGIN)  )
	{
		// Turn off Cooler and Turn Heater off
		HeatingElement_OFF();
		CoolingElement_OFF();
		
	}
	// Required Temperature is higher than room temperature, so heat the room
	else if(Temp_Set >Temp_AVG - TEMP_MARGIN )
	{
		// Turn on Heater and turn Cooler off
		HeatingElement_ON();
		CoolingElement_OFF();
	}
// Required Temperature is lower than room temperature, so cool the room
	else if (Temp_Set < Temp_AVG + TEMP_MARGIN)
	{
		// Turn on Cooler and Turn Heater off
		HeatingElement_OFF();
		CoolingElement_ON();
	}

	
}

void TemperatureMonitoringTask()
{
	// Check if the system is ON and the heating element is active
	if ((System_Mode == SYSTEM_ON) && (DIO_u8_Get_Pin_Val(HEATINGELEMENT_PORT, HEATINGELEMENT_PIN) == HIGH))
	{
		HeatingElement_Led_TOGGLE();
	}
	else
	{
		Heating_ElementLed_OFF();
	}
	 // Check if the system is in setting mode
	if (SettingMode_Flag == 1)
	{
		// Toggle Seven Segment Display
		SSD_TOGGLE();
	}
	// Check if the system is ON
	if (System_Mode == SYSTEM_ON)
	{
		counter_5sec++;

		_delay_ms(50);
	// Check if 5 seconds have passed
		if (counter_5sec > 5)
		{
			counter_up = 0;
			counter_down = 0;
			// Enable Seven Segment Display and show average temperature
			SSD_EN();
			SEVEN_SEGMENT_Write_Val(Temp_AVG);
			SettingMode_Flag = 0;
		}
		else
		{
			// Enable Seven Segment Display and show current temperature setting
			SSD_EN();
			SEVEN_SEGMENT_Write_Val(Temp_Set);
			SettingMode_Flag = 1;
		}
	}
}
