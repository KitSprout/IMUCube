/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "drivers\stm32f1_spi.h"

#include "module_MPU6500.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define SPIx                  SPI1
#define SPIx_CLK()            RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE)
#define SPIx_SPEED_HIGH       SPI_BaudRatePrescaler_2
#define SPIx_SPEED_LOW        SPI_BaudRatePrescaler_256

#define SPIx_CS_PIN           GPIO_Pin_4
#define SPIx_CS_GPIO_PORT     GPIOA
#define SPIx_CS_GPIO_CLK()    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)
#define SPIx_CS_H()           __GPIO_SET(SPIx_CS_GPIO_PORT, SPIx_CS_PIN)
#define SPIx_CS_L()           __GPIO_RST(SPIx_CS_GPIO_PORT, SPIx_CS_PIN)

#define SPIx_SCK_PIN          GPIO_Pin_5
#define SPIx_SCK_GPIO_PORT    GPIOA
#define SPIx_SCK_GPIO_CLK()   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

#define SPIx_SDO_PIN          GPIO_Pin_6
#define SPIx_SDO_GPIO_PORT    GPIOA
#define SPIx_SDO_GPIO_CLK()   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

#define SPIx_SDI_PIN          GPIO_Pin_7
#define SPIx_SDI_GPIO_PORT    GPIOA
#define SPIx_SDI_GPIO_CLK()   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)
/*====================================================================================================*/
/*====================================================================================================*/
static SPI_InitTypeDef MPUx_InitStruct;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_WriteReg
**功能 : Write Reg
**輸入 : writeAddr, writeData
**輸出 : None
**使用 : MPU6500_WriteReg(writeAddr, writeData);
**====================================================================================================*/
/*====================================================================================================*/
void MPU6500_WriteReg( uint8_t writeAddr, uint8_t writeData )
{
  SPIx_CS_L();
  SPI_RW(SPIx, writeAddr);
  SPI_RW(SPIx, writeData);
  SPIx_CS_H();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_WriteRegs
**功能 : Write Regs
**輸入 : writeAddr, *writeData, lens
**輸出 : None
**使用 : MPU6500_WriteRegs(writeAddr, writeData, lens);
**====================================================================================================*/
/*====================================================================================================*/
void MPU6500_WriteRegs( uint8_t writeAddr, uint8_t *writeData, uint8_t lens )
{
  SPIx_CS_L();
  SPI_RW(SPIx, writeAddr);
  for(uint8_t i = 0; i < lens; i++)
    SPI_RW(SPIx, writeData[i]);
  SPIx_CS_H();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_ReadReg
**功能 : Read Reg
**輸入 : readAddr
**輸出 : readData
**使用 : readData = MPU6500_ReadReg(readAddr);
**====================================================================================================*/
/*====================================================================================================*/
uint8_t MPU6500_ReadReg( uint8_t readAddr )
{
  uint8_t readData = 0;

  SPIx_CS_L();
  SPI_RW(SPIx, 0x80 | readAddr);
  readData = SPI_RW(SPIx, 0x00);
  SPIx_CS_H();

  return readData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU6500_ReadRegs
**功能 : Read Regs
**輸入 : readAddr, *readData, lens
**輸出 : None
**使用 : MPU6500_ReadRegs(MPU6500_ACCEL_XOUT_H, readData, 14);
**=====================================================================================================*/
/*=====================================================================================================*/
void MPU6500_ReadRegs( uint8_t readAddr, uint8_t *readData, uint8_t lens )
{
  SPIx_CS_L();
  SPI_RW(SPIx, 0x80 | readAddr);
  for(uint8_t i = 0; i < lens; i++)
    readData[i] = SPI_RW(SPIx, 0x00);
  SPIx_CS_H();
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_SetSpeed
**功能 : Set SPI Speed
**輸入 : SpeedSel
**輸出 : None
**使用 : MPU6500_SetSpeed(SPIx_SPEED_LOW);
**====================================================================================================*/
/*====================================================================================================*/
void MPU6500_SetSpeed( uint8_t speedSel )
{
  SPI_Cmd(SPIx, DISABLE);

  MPUx_InitStruct.SPI_BaudRatePrescaler = speedSel;
  SPI_Init(SPIx, &MPUx_InitStruct);

  SPI_Cmd(SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_Config
**功能 : MPU6500 Config
**輸入 : None
**輸出 : None
**使用 : MPU6500_Config();
**====================================================================================================*/
/*====================================================================================================*/
void MPU6500_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* SPI Clk *******************************************************************/
  SPIx_CLK();
  SPIx_CS_GPIO_CLK();
  SPIx_SCK_GPIO_CLK();
  SPIx_SDO_GPIO_CLK();
  SPIx_SDI_GPIO_CLK();

  /* SPI GPIO ******************************************************************/
  GPIO_InitStruct.GPIO_Pin   = SPIx_CS_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(SPIx_CS_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = SPIx_SCK_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
  GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = SPIx_SDO_PIN;
  GPIO_Init(SPIx_SDO_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = SPIx_SDI_PIN;
  GPIO_Init(SPIx_SDI_GPIO_PORT, &GPIO_InitStruct);

  SPIx_CS_H();  // LOW ENABLE

  /* SPI Init ******************************************************************/
  MPUx_InitStruct.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
  MPUx_InitStruct.SPI_Mode              = SPI_Mode_Master;
  MPUx_InitStruct.SPI_DataSize          = SPI_DataSize_8b;
  MPUx_InitStruct.SPI_CPOL              = SPI_CPOL_High;
  MPUx_InitStruct.SPI_CPHA              = SPI_CPHA_2Edge;
  MPUx_InitStruct.SPI_NSS               = SPI_NSS_Soft;
  MPUx_InitStruct.SPI_BaudRatePrescaler = SPIx_SPEED_LOW;
  MPUx_InitStruct.SPI_FirstBit          = SPI_FirstBit_MSB;
  MPUx_InitStruct.SPI_CRCPolynomial     = 7;
  SPI_Init(SPIx, &MPUx_InitStruct);

  SPI_Cmd(SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_Init
**功能 : Init MPU6500
**輸入 : None
**輸出 : status
**使用 : status = MPU6500_Init(&MPUx_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
#define MPU6500_InitRegNum 11
uint8_t MPU6500_Init( MPU_InitTypeDef *MPUx )
{
  uint8_t status = ERROR;
  uint8_t MPU6500_InitData[MPU6500_InitRegNum][2] = {
    {0x80, MPU6500_PWR_MGMT_1},     // [0]  Reset Device
    {0x04, MPU6500_PWR_MGMT_1},     // [1]  Clock Source
    {0x10, MPU6500_INT_PIN_CFG},    // [2]  Set INT_ANYRD_2CLEAR
    {0x01, MPU6500_INT_ENABLE},     // [3]  Set RAW_RDY_EN
    {0x00, MPU6500_PWR_MGMT_2},     // [4]  Enable Acc & Gyro
    {0x00, MPU6500_SMPLRT_DIV},     // [5]  Sample Rate Divider
    {0x18, MPU6500_GYRO_CONFIG},    // [6]  default : +-2000dps
    {0x08, MPU6500_ACCEL_CONFIG},   // [7]  default : +-4G
    {0x07, MPU6500_CONFIG},         // [8]  default : LPS_41Hz
    {0x03, MPU6500_ACCEL_CONFIG_2}, // [9]  default : LPS_41Hz
    {0x30, MPU6500_USER_CTRL},      // [10] Set I2C_MST_EN, I2C_IF_DIS
  };

  MPU6500_InitData[6][0] = MPUx->MPU_Gyr_FullScale;       // MPU6500_GYRO_CONFIG
  MPU6500_InitData[8][0] = MPUx->MPU_Gyr_LowPassFilter;   // MPU6500_CONFIG
  MPU6500_InitData[7][0] = MPUx->MPU_Acc_FullScale;       // MPU6500_ACCEL_CONFIG
  MPU6500_InitData[9][0] = MPUx->MPU_Acc_LowPassFilter;   // MPU6500_ACCEL_CONFIG_2

  for(uint8_t i = 0; i < MPU6500_InitRegNum; i++) {
    delay_ms(2);
    MPU6500_WriteReg(MPU6500_InitData[i][1], MPU6500_InitData[i][0]);
  }

  status = MPU6500_Check();
  if(status != SUCCESS)
    return ERROR;

  delay_ms(10);

  MPU6500_SetSpeed(SPIx_SPEED_HIGH);
  delay_ms(10);

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_Check
**功能 : Check Device ID
**輸入 : None
**輸出 : Status
**使用 : Status = MPU6500_Check();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t MPU6500_Check( void )
{
  uint8_t deviceID = ERROR;

  deviceID = MPU6500_ReadReg(MPU6500_WHO_AM_I);
  if(deviceID != MPU6500_Device_ID)
    return ERROR;

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU6500_getData
**功能 : Get IMU Data
**輸入 : *dataIMU
**輸出 : None
**使用 : MPU6500_getData(dataIMU);
**====================================================================================================*/
/*====================================================================================================*/
void MPU6500_getData( int16_t *dataIMU )
{
  uint8_t tmpRead[22] = {0};

  MPU6500_ReadRegs(MPU6500_ACCEL_XOUT_H, tmpRead, 14);

  dataIMU[0] = (Byte16(int16_t, tmpRead[6],  tmpRead[7]));    // Temp
  dataIMU[1] = (Byte16(int16_t, tmpRead[0],  tmpRead[1]));    // Acc.X
  dataIMU[2] = (Byte16(int16_t, tmpRead[2],  tmpRead[3]));    // Acc.Y
  dataIMU[3] = (Byte16(int16_t, tmpRead[4],  tmpRead[5]));    // Acc.Z
  dataIMU[4] = (Byte16(int16_t, tmpRead[8],  tmpRead[9]));    // Gyr.X
  dataIMU[5] = (Byte16(int16_t, tmpRead[10], tmpRead[11]));   // Gyr.Y
  dataIMU[6] = (Byte16(int16_t, tmpRead[12], tmpRead[13]));   // Gyr.Z
}
/*==============================================================================================*/
/*==============================================================================================*/
