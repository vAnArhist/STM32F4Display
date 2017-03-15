#ifndef _XPT2046_H_
#define _XPT2046_H_
#define XPT_CS_ON HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
#define XPT_CS_OFF HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
#include "GUI.h"

void XPT2046_Init(void);
int touchGetX(void);
int touchGetY(void);
void GetTouchState (void);
void Callibrate(void);
void Usrednenie_XY(int touch_x, int touch_y, uint8_t count_read);

typedef struct {
	unsigned char Pressed;
	int x;
	int y;
    unsigned char Layer;
} TS_State_struct;

#endif
