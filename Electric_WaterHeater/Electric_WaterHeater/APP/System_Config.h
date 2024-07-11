

#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_


#define ON_OFF_PORT         PORTD
#define ON_OFF_PIN          PIN2
#define UP_BUTTON_PORT      PORTD
#define UP_BUTTON_PIN       PIN3
#define DOWN_BUTTON_PORT    PORTB
#define DOWN_BUTTON_PIN     PIN2
#define TEMP_SENSOR_PIN	    PIN0



#define LED_ON          0
#define LED_BLINK       1

#define SYSTEM_OFF      0
#define SYSTEM_ON       1

#define TEMP_INIT       60
#define TEMP_MARGIN     5

extern u32 OF_Count ;
u8 System_Mode= SYSTEM_OFF;
u8 Temp_Set =  TEMP_INIT;
u16 Temp_Curr =  TEMP_INIT;
u8 Temp_AVG =  TEMP_INIT;


#endif /* SYSTEM_CONFIG_H_ */