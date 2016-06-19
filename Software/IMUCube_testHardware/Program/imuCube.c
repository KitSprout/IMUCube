/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_system.h"
#include "drivers\nrf5x_adc.h"
#include "modules\module_serial.h"
#include "modules\module_mpu9250.h"
#include "modules\module_ws2812b.h"

#include "imuCube.h"
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_Init( void )
{
  IMUCube_CKOCK_Config();
  IMUCube_GPIO_Config();
  IMUCube_ADC_Config();
  IMUCube_UART_Config();
  IMUCube_MPU9250_Config();
  IMUCube_WS2812B_Config();
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_Loop( void )
{
  int16_t imu[10] = {0};
  float vol = 0;

  WS2812B_testRainbow();
  WS2812B_Clear();

  while(1) {
    delay_ms(100);
    while(KEY_Read()) {
      BUZ_Toggle();
      MOT_Set();
      delay_ms(1);
    }
    MOT_Reset();
    BUZ_Reset();
    MPU9250_getData(imu);
    vol = ADC_Read(NRF_ADC_CONFIG_INPUT_7) * BATTERY_VOL_CONV;
    printf("AX:%5i\tAY:%5i\tAZ:%5i\tGX:%5i\tGY:%5i\tGZ:%5i\tMX:%5i\tMY:%5i\tMZ:%5i\tVB:%.2f\r\n", imu[1], imu[2], imu[3], imu[4], imu[5], imu[6], imu[7], imu[8], imu[9], vol);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
