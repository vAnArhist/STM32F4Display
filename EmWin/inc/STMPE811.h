#ifndef STMPE811_H
#define STMPE811_H

#include "stm32f4xx_hal.h"
#include "GUI.h"

typedef struct {
	uint16_t Touch_Detect;
	uint16_t X;
	uint16_t Y;
} TS_State_struct;


void ID_read(void);
void Read_X(void);
void stmpe811_ini(void);
void Read_stmpe811(void);
#endif
