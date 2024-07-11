#include "APP/System.h"
#define F_CPU 16000000UL
#include "util/delay.h"

int main(void)
{
	EEPROM_Init();
	System_Init();

	while (1)
	{
	}
}
