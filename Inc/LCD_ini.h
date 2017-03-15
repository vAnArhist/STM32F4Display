#ifndef LCD_INI_H
#define LCD_INI_H

#define Clr_Cs          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_RESET)
#define Set_Cs          HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, GPIO_PIN_SET)

#define Set_nWr         HAL_GPIO_WritePin(GPIOD , GPIO_PIN_5, GPIO_PIN_SET);
#define Clr_nWr         HAL_GPIO_WritePin(GPIOD , GPIO_PIN_5, GPIO_PIN_RESET);

#define Set_nRd         HAL_GPIO_WritePin(GPIOD , GPIO_PIN_4, GPIO_PIN_SET);
#define Clr_nRd         HAL_GPIO_WritePin(GPIOD , GPIO_PIN_4, GPIO_PIN_RESET);

#define Set_Rs          HAL_GPIO_WritePin(GPIOE , GPIO_PIN_3, GPIO_PIN_SET);
#define Clr_Rs          HAL_GPIO_WritePin(GPIOE , GPIO_PIN_3, GPIO_PIN_RESET);

#include "stm32f4xx_hal.h"
#define CMD_ADR *(uint16_t *)0x60000000 //запись команд
#define DAT_ADR *(uint16_t *)0x60100000 //запись данных (А19+1 влево) 
#define ILI9325_DATA_REG 0x22	        //RAM DATA REGISTER LCD
void LCD_ini(void);
void LCD_Clear(uint16_t color);

#endif
