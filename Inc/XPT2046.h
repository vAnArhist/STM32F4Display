#ifndef _XPT2046_H_
#define _XPT2046_H_
#define XPT_CS_ON HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
#define XPT_CS_OFF HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
#include "GUI.h"

void XPT2046_Init(void);
void touchGetX(void);
void touchGetY(void);
void GetTouchState (void);


typedef struct {
	unsigned char Pressed;
	int x;
	int y;
    unsigned char Layer;
} TS_State_struct;

#endif
