
#ifndef EEPROM_CONFIG_H_
#define EEPROM_CONFIG_H_

#define EEARL_REG *((volatile u8 *)0x3E)
#define EEARH_REG *((volatile u8 *)0x3F)
#define EECR_REG *((volatile u8 *)0x3C)
#define EEDR_REG *((volatile u8 *)0x3D)

/* EEPROM Control Register */
#define EERIE 3
#define EEMWE 2
#define EEWE 1
#define EERE 0

#endif /* EEPROM_CONFIG_H_ */