#ifndef LCD_INI_H
#define LCD_INI_H

#include "stm32f4xx_hal.h"

#define CMD_ADR			*(uint16_t *)0x60000000
#define DAT_ADR			*(uint16_t *)0x60100000

#define SSD2119_DATA_REG		0x22

void LCD_ini(void);
void LCD_Clear(uint16_t color);

#endif
