/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "modules\module_serial.h"
#include "modules\module_MPU6500.h"

#include "imuCube.h"
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_Init( void )
{
  MPU_InitTypeDef MPU_InitStruct;

  SystemInit();
  HAL_InitTick();

  Serial_Config();
  MPU6500_Config();

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
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_Loop( void )
{
  int16_t IMU_Buf[10] = {0};

  MPU6500_getData(IMU_Buf);
  printf("Acc.X = %d\tAcc.Y = %d\tAcc.Z = %d\tGyr.X = %d\tGyr.Y = %d\tGyr.Z = %d\tTemp = %d\r\n", IMU_Buf[1], IMU_Buf[2], IMU_Buf[3], IMU_Buf[4], IMU_Buf[5], IMU_Buf[6], IMU_Buf[0]);
  delay_ms(200);
}
/*====================================================================================================*/
/*====================================================================================================*/
