#include "stm32f4xx.h"
#include "XPT2046.h"
#include "GUI.h"
#define Xmax 3668
#define Xmin 466
#define Xwork 3202
/*На 240 точек по Х приходится 3202 ур.н.,т.е: 1 к 13.34*/
/*На 320 точек по У приходится 3538 ур.н.,т.е: 1 к 11.05*/
#define Ymax 3772
#define Ymin 234
#define Ywork 3538
////////////////////////////////////////////////////////////////////////////////
extern SPI_HandleTypeDef hspi2;
unsigned char touch_en;
TS_State_struct TS_State;
int touch_y, touch_x;
uint8_t count_read = 10;
//////////////////////////////////////////////////////////////////////////////

GUI_PID_STATE TS_PID_State;

void GetTouchState (void){
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET){
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
    touch_en = 1;
    TS_State.Pressed = touch_en;
    TS_PID_State.Pressed = touch_en;
    TS_PID_State.Layer = 0;
    }
    else{
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
    touch_en = 0;
    TS_State.Pressed = 0;
    TS_PID_State.Pressed = 0;
    TS_PID_State.Layer = 0;
    TS_PID_State.x = 0;
    TS_PID_State.y = 0;
    GUI_TOUCH_StoreStateEx(&TS_PID_State);
   }
}

void XPT2046_Init(void){
  uint8_t adress;
  
  XPT_CS_ON;
  adress=0x80;
  HAL_SPI_Transmit(&hspi2,&adress,1,1000);
  adress=0x00;
  HAL_SPI_Transmit(&hspi2,&adress,1,1000);
  adress=0x00;
  HAL_SPI_Transmit(&hspi2,&adress,1,1000);
  XPT_CS_OFF;}

int touchGetX(void){
  uint16_t LSB, MSB;
  uint8_t adress;
  uint8_t dataX;
  touch_x = 0;
  XPT_CS_ON;
  adress = 0xD0;
  HAL_SPI_Transmit(&hspi2,&adress,1,1000);
  adress = 0x00;
  HAL_SPI_TransmitReceive(&hspi2, &adress, &dataX, sizeof(dataX), 1000);
  MSB = dataX;
  adress = 0x00;
  HAL_SPI_TransmitReceive(&hspi2,&adress, &dataX, sizeof(dataX), 1000);
  LSB = dataX;
  XPT_CS_ON;
  touch_x = ((MSB<<8)|(LSB))>>3;
  touch_x -= 300;
  touch_x =  touch_x/15;
  TS_State.x = touch_x;
  TS_PID_State.x = touch_x;
  return touch_x;
}

int touchGetY(void){
  uint16_t LSB, MSB;
  uint8_t adress;
  uint8_t dataY;
  touch_y = 0;
  XPT_CS_ON;
  adress = 0x90;
  HAL_SPI_Transmit(&hspi2,&adress,1,1000);
  adress = 0x00;
  HAL_SPI_TransmitReceive(&hspi2,&adress, &dataY, sizeof(dataY), 1000);
  MSB = dataY;
  adress = 0x00;
  HAL_SPI_TransmitReceive(&hspi2,&adress, &dataY, sizeof(dataY), 1000);
  LSB = dataY;
  XPT_CS_ON;
  touch_y = ((MSB<<8)|(LSB))>>3;
  touch_y -= 350;
  touch_y =  touch_y/11;
  TS_State.y = touch_y;
  TS_PID_State.y = touch_y;
  return touch_y;
}

void Usrednenie_XY(int touch_x, int touch_y, uint8_t count_read){  
  int tmpx, tmpy = 0;
  for(uint8_t i=0; i<count_read; i++){
  tmpx = touchGetX();
  tmpy = touchGetY();
  touch_x = (touch_x+tmpx)/2;
  touch_y = (touch_y+tmpy)/2;
  }
}
void Callibrate(void){
 /*На 240 точек по Х приходится 3202 ур.н.,т.е: 1 к 13.34*/
/*На 320 точек по У приходится 3538 ур.н.,т.е: 1 к 11.05*/
  if ((touch_x < LCD_GetXSize()) && (touch_y<LCD_GetYSize())){
    //GUI_TOUCH_StoreUnstable(touch_x,touch_y);}
    //GUI_PID_GetCurrentState(&TS_PID_State);
    GUI_TOUCH_StoreStateEx(&TS_PID_State);
  }
}
