/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "modules\module_serial.h"
#include "modules\module_MPU6500.h"
#include "modules\module_ws2812b.h"

#include "imuCube.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define COLOR_R 8
#define COLOR_G 8
#define COLOR_B 8

void IMUCube_Init( void )
{
  MPU_InitTypeDef MPU_InitStruct;

  SystemInit();
  HAL_InitTick();

  Serial_Config();
  MPU6500_Config();
  WS2812B_Config();

  printf("\r\nHello World!!\r\n\r\n");

  MPU_InitStruct.MPU_Gyr_FullScale     = MPU_GyrFS_2000dps;
  MPU_InitStruct.MPU_Gyr_LowPassFilter = MPU_GyrLPS_41Hz;
  MPU_InitStruct.MPU_Acc_FullScale     = MPU_AccFS_4g;
  MPU_InitStruct.MPU_Acc_LowPassFilter = MPU_AccLPS_41Hz;
  while(MPU6500_Init(&MPU_InitStruct) != SUCCESS) {
    printf("Init ERROR!!\r\n");
    delay_ms(100);
  }
  printf("Init SUCCESS!!\r\n");

  WS2812B_clearAll(0, 0, 0);
  delay_ms(100);
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_Loop( void )
{
  static uint8_t state = 0;
  static uint8_t intStageNum = 0;
  static uint8_t r = 16, g = 0, b = 0;
  static uint8_t tmpCount = 0;

  int16_t IMU_Buf[10] = {0};
  int16_t color[3]    = {0};

  delay_ms(1);
  MPU6500_getData(IMU_Buf);
  if((IMU_Buf[2] > 9000) || (IMU_Buf[2] < -9000))
    state = !state;

  if(state) {
    if(tmpCount++ > 50) {
      tmpCount = 0;
      switch(intStageNum) {
        case 0: { g++; if(g == 16) { intStageNum = 1;}  break; }
        case 1: { r--; if(r == 0)  { intStageNum = 2;}  break; }
        case 2: { b++; if(b == 16) { intStageNum = 3;}  break; }
        case 3: { g--; if(g == 0)  { intStageNum = 4;}  break; }
        case 4: { r++; if(r == 16) { intStageNum = 5;}  break; }
        case 5: { b--; if(b == 0)  { intStageNum = 0;}  break; }
      }
      for(uint8_t j = 0; j < WS2812B_LENS; j++) {
        WS2812B_rgb[j][0] = g;
        WS2812B_rgb[j][1] = r;
        WS2812B_rgb[j][2] = b;
      }

      WS2812B_sendData(0, WS2812B_LENS - 1);
    }
  }
  else {
    color[0] = (IMU_Buf[0] + 8192) / 1000;
    color[1] = (IMU_Buf[1] + 8192) / 800;
    color[2] = (IMU_Buf[2] + 8192) / 600;
    if(color[0] < 0) color[0] = 0; else if(color[0] > 255) color[0] = 255;
    if(color[1] < 0) color[1] = 0; else if(color[1] > 255) color[1] = 255;
    if(color[2] < 0) color[2] = 0; else if(color[2] > 255) color[2] = 255;
    WS2812B_clearAll(color[0], color[1], color[2]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : WS2812B_sendPixel
**功能 : WS2812B Send Pixel
**輸入 : led, r, g, b
**輸出 : None
**使用 : WS2812B_sendPixel(led, r, g, b);
**====================================================================================================*/
/*====================================================================================================*/
//void WS2812B_setDice( uint16_t cols, uint16_t rows, uint8_t r, uint8_t g, uint8_t b )
//{
//  uint8_t led = WS2812B_ROWS * cols + rows;
//  uint8_t tmpData = 0;
//  uint16_t memAddr = 24 * led;

//  WS2812B_rgb[led][0] = g;
//  WS2812B_rgb[led][1] = r;
//  WS2812B_rgb[led][2] = b;

//  for(uint8_t i = 0; i < 3; i++) {
//    tmpData = WS2812B_rgb[led][i];
//    for(uint8_t j = 0; j < 8; j++) {
//      WS2812B_dmaBuf[memAddr++] = WS2812B_LOGIC(tmpData);
//      tmpData <<= 1;
//    }
//	}

//  WS2812B_DMA_SEND();
//}
/*====================================================================================================*/
/*====================================================================================================*/
