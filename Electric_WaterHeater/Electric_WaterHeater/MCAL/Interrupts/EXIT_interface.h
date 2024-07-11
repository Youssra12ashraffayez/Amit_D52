

#ifndef EXIT_INTERFACE_H_
#define EXIT_INTERFACE_H_

#define RISING_EDGE 0
#define FALLING_EDGE 1
#define ANY_LOGIC_CHANGE 2
#define LOW_LEVEL 3

void EXT_Vid_Interrupt_Init0(u8 SENSE_CONTROL);
void EXT_Vid_Interrupt_Init1(u8 SENSE_CONTROL);
void EXT_Vid_Interrupt_Init2(u8 SENSE_CONTROL);
void EXT_Vid_Interrupt0();
void EXT_Vid_Interrupt1();
void EXT_Vid_Interrupt2();
void EXT_Vid_Set_CallBack(void (*ptr_set_callback)(void));
void EXT_Vid_Set_CallBack_2(void (*ptr_set_callback)(void));
void EXT_Vid_Set_CallBack_3(void (*ptr_set_callback)(void));

#endif /* EXIT_INTERFACE_H_ */