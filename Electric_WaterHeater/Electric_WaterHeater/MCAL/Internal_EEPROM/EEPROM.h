

#ifndef EEPROM_H_
#define EEPROM_H_

void EEPROM_Send(u16 copy_u16_addr, u8 copy_u16_data);

unsigned char EEPROM_Recieve(u16 copy_u16_addr);

#endif /* EEPROM_H_ */