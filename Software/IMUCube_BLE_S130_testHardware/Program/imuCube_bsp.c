/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_adc.h"
#include "modules\module_serial.h"
#include "modules\module_mpu9250.h"
#include "modules\module_ws2812b.h"
#include "applications\app_kSerial.h"

#include "imuCube_bsp.h"
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_CKOCK_Config( void )
{
  nrf_drv_clock_init();
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_GPIO_Config( void )
{
  nrf_gpio_cfg(KEY, NRF_GPIO_PIN_DIR_INPUT,
                    NRF_GPIO_PIN_INPUT_CONNECT,
                    NRF_GPIO_PIN_PULLDOWN,
                    NRF_GPIO_PIN_S0S1,
                    NRF_GPIO_PIN_NOSENSE);
  nrf_gpio_cfg(BUZ, NRF_GPIO_PIN_DIR_OUTPUT,
                    NRF_GPIO_PIN_INPUT_DISCONNECT,
                    NRF_GPIO_PIN_NOPULL,
                    NRF_GPIO_PIN_S0S1,
                    NRF_GPIO_PIN_NOSENSE);
  nrf_gpio_cfg(MOT, NRF_GPIO_PIN_DIR_OUTPUT,
                    NRF_GPIO_PIN_INPUT_DISCONNECT,
                    NRF_GPIO_PIN_NOPULL,
                    NRF_GPIO_PIN_S0S1,
                    NRF_GPIO_PIN_NOSENSE);

  BUZ_Reset();
  MOT_Reset();
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_ADC_Config( void )
{
  ADC_Config();
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_UART_Config( void )
{
  Serial_Config();
  printf("\fHello World!!\r\n");

  kSerial_Config(Serial_SendByte);
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_MPU9250_Config( void )
{
  MPU_ConfigTypeDef MPU_ConfigStruct;

  MPU9250_Config();
  delay_ms(10);

  MPU_ConfigStruct.MPU_Gyr_FullScale     = MPU_GyrFS_2000dps;
  MPU_ConfigStruct.MPU_Gyr_LowPassFilter = MPU_GyrLPS_41Hz;
  MPU_ConfigStruct.MPU_Acc_FullScale     = MPU_AccFS_4g;
  MPU_ConfigStruct.MPU_Acc_LowPassFilter = MPU_AccLPS_41Hz;
  while(MPU9250_Init(&MPU_ConfigStruct) != SUCCESS) {
    printf("MPU9250 INIT ERROR!!\r\n");
    delay_ms(100);
  }
  printf("MPU9250 INIT SUCCESS!!\r\n");
  delay_ms(50);
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_WS2812B_Config( void )
{
  WS2812B_Config();
}
/*====================================================================================================*/
/*====================================================================================================*/
