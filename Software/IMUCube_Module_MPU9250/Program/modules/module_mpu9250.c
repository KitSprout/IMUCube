/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_spi.h"

#include "module_mpu9250.h"

#include "app_util_platform.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define _USE_MAG_AK8963
#define MAG_READ_DELAY 256
/*====================================================================================================*/
/*====================================================================================================*/
#define READ_BUF_SIZE   24
#define WRITW_BUF_SIZE  2

static uint8_t readBuf[READ_BUF_SIZE] = {0};
static uint8_t writeBuf[WRITW_BUF_SIZE] = {0};
static nrf_drv_kspi_t SPIx = { NRF_DRV_SPI_INSTANCE(SPI0_INSTANCE_INDEX), false};

#ifdef _USE_MAG_AK8963
/*static*/ int16_t AK8963_ASA[3] = {0};
#endif
/**====================================================================================================*/
/*====================================================================================================*/
void mpu9250_spi_event_handler( nrf_drv_spi_evt_t const * p_event )
{
  SPIx.flag = true;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9250_WriteReg
**功能 : Write Reg
**輸入 : writeAddr, writeData
**輸出 : None
**使用 : MPU9250_WriteReg(writeAddr, writeData);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9250_WriteReg( uint8_t writeAddr, uint8_t writeData )
{
  writeBuf[0] = writeAddr;
  writeBuf[1] = writeData;
  SPI_RW(&SPIx, writeBuf, 2, readBuf, 0);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9250_WriteRegs
**功能 : Write Regs
**輸入 : writeAddr, *writeData, lens
**輸出 : None
**使用 : MPU9250_WriteRegs(writeAddr, writeData, lens);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9250_WriteRegs( uint8_t writeAddr, uint8_t *writeData, uint8_t lens )
{
  writeBuf[0] = writeAddr;
  for(uint8_t i = 0; i < lens; i++)
    writeBuf[i + 1] = writeData[i];
  SPI_RW(&SPIx, writeBuf, lens + 1, readBuf, 0);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9250_ReadReg
**功能 : Read Reg
**輸入 : readAddr
**輸出 : readData
**使用 : readData = MPU9250_ReadReg(readAddr);
**====================================================================================================*/
/*====================================================================================================*/
uint8_t MPU9250_ReadReg( uint8_t readAddr )
{
  writeBuf[0] = 0x80 | readAddr;
  SPI_RW(&SPIx, writeBuf, 1, readBuf, 2);

  return readBuf[1];
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU9250_ReadRegs
**功能 : Read Regs
**輸入 : readAddr, *readData, lens
**輸出 : None
**使用 : MPU9250_ReadRegs(MPU6500_ACCEL_XOUT_H, readData, 14);
**=====================================================================================================*/
/*=====================================================================================================*/
void MPU9250_ReadRegs( uint8_t readAddr, uint8_t *readData, uint8_t lens )
{
  writeBuf[0] = 0x80 | readAddr;
  SPI_RW(&SPIx, writeBuf, 1, readBuf, lens + 1);
  for(uint8_t i = 0; i < lens; i++)
    readData[i] = readBuf[i + 1];
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU9250_Mag_WriteReg
**功能 : AK8963 Write Reg
**輸入 : writeAddr, writeData
**輸出 : None
**使用 : MPU9250_Mag_WriteReg(AK8963_CNTL2, 0x01);
**=====================================================================================================*/
/*=====================================================================================================*/
#ifdef _USE_MAG_AK8963
void MPU9250_Mag_WriteReg( uint8_t writeAddr, uint8_t writeData )
{
  uint8_t  status = 0;
  uint32_t timeout = MAG_READ_DELAY;

  MPU9250_WriteReg(MPU6500_I2C_SLV4_ADDR, AK8963_I2C_ADDR);
  delay_ms(1);
  MPU9250_WriteReg(MPU6500_I2C_SLV4_REG, writeAddr);
  delay_ms(1);
  MPU9250_WriteReg(MPU6500_I2C_SLV4_DO, writeData);
  delay_ms(1);
  MPU9250_WriteReg(MPU6500_I2C_SLV4_CTRL, MPU6500_I2C_SLVx_EN);
  delay_ms(1);

  do {
    status = MPU9250_ReadReg(MPU6500_I2C_MST_STATUS);
    delay_ms(1);
  } while(((status & MPU6500_I2C_SLV4_DONE) == 0) && (timeout--));
}
#endif
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU9250_Mag_WriteRegs
**功能 : AK8963 Write Regs
**輸入 : writeAddr, *writeData, lens
**輸出 : None
**使用 : MPU9250_Mag_WriteRegs(AK8963_CNTL2, 0x01);
**=====================================================================================================*/
/*=====================================================================================================*/
#ifdef _USE_MAG_AK8963
void MPU9250_Mag_WriteRegs( uint8_t writeAddr, uint8_t *writeData, uint8_t lens )
{
  uint8_t  status = 0;
  uint32_t timeout = MAG_READ_DELAY;

  MPU9250_WriteReg(MPU6500_I2C_SLV4_ADDR, AK8963_I2C_ADDR);
  delay_ms(1);
  for(uint8_t i = 0; i < lens; i++) {
    MPU9250_WriteReg(MPU6500_I2C_SLV4_REG, writeAddr + i);
    delay_ms(1);
    MPU9250_WriteReg(MPU6500_I2C_SLV4_DO, writeData[i]);
    delay_ms(1);
    MPU9250_WriteReg(MPU6500_I2C_SLV4_CTRL, MPU6500_I2C_SLVx_EN);
    delay_ms(1);

    do {
      status = MPU9250_ReadReg(MPU6500_I2C_MST_STATUS);
    } while(((status & MPU6500_I2C_SLV4_DONE) == 0) && (timeout--));
  }
}
#endif
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU9250_Mag_ReadReg
**功能 : AK8963 Read Reg
**輸入 : readAddr
**輸出 : readData
**使用 : DeviceID = MPU9250_Mag_ReadReg(AK8963_WIA);
**=====================================================================================================*/
/*=====================================================================================================*/
#ifdef _USE_MAG_AK8963
uint8_t MPU9250_Mag_ReadReg( uint8_t readAddr )
{
  uint8_t status = 0;
  uint8_t readData = 0;
  uint32_t timeout = MAG_READ_DELAY;

  MPU9250_WriteReg(MPU6500_I2C_SLV4_ADDR, AK8963_I2C_ADDR | 0x80);
  delay_ms(1);
  MPU9250_WriteReg(MPU6500_I2C_SLV4_REG, readAddr);
  delay_ms(1);
  MPU9250_WriteReg(MPU6500_I2C_SLV4_CTRL, MPU6500_I2C_SLVx_EN);
  delay_ms(1);

  do {
    status = MPU9250_ReadReg(MPU6500_I2C_MST_STATUS);
    delay_ms(1);
  } while(((status & MPU6500_I2C_SLV4_DONE) == 0) && (timeout--));

  readData = MPU9250_ReadReg(MPU6500_I2C_SLV4_DI);

  return readData;
}
#endif
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU9250_Mag_ReadRegs
**功能 : AK8963 Read Regs
**輸入 : readAddr, *readData, lens
**輸出 : None
**使用 : DeviceID = MPU9250_Mag_ReadRegs(AK8963_WIA);
**=====================================================================================================*/
/*=====================================================================================================*/
#ifdef _USE_MAG_AK8963
void MPU9250_Mag_ReadRegs( uint8_t readAddr, uint8_t *readData, uint8_t lens )
{
  uint8_t status = 0;
  uint32_t timeout = MAG_READ_DELAY;

  MPU9250_WriteReg(MPU6500_I2C_SLV4_ADDR, AK8963_I2C_ADDR | 0x80);
  delay_ms(1);
  for(uint8_t i = 0; i< lens; i++) {
    MPU9250_WriteReg(MPU6500_I2C_SLV4_REG, readAddr + i);
    delay_ms(1);
    MPU9250_WriteReg(MPU6500_I2C_SLV4_CTRL, MPU6500_I2C_SLVx_EN);
    delay_ms(1);

    do {
      status = MPU9250_ReadReg(MPU6500_I2C_MST_STATUS);
    } while(((status & MPU6500_I2C_SLV4_DONE) == 0) && (timeout--));

    readData[i] = MPU9250_ReadReg(MPU6500_I2C_SLV4_DI);
    delay_ms(1);
  }
}
#endif
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9250_SetSpeed
**功能 : Set SPI Speed
**輸入 : SpeedSel
**輸出 : None
**使用 : MPU9250_SetSpeed(SPIx_SPEED_LOW);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9250_SetSpeed( uint8_t speedSel )
{

}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9250_Config
**功能 : SPI Config
**輸入 : None
**輸出 : None
**使用 : MPU9250_Config();
**====================================================================================================*/
/*====================================================================================================*/
void MPU9250_Config( void )
{
  nrf_drv_spi_config_t spi_init_struct = {0};

  spi_init_struct.ss_pin        = SPI0_CONFIG_CS_PIN;
  spi_init_struct.sck_pin       = SPI0_CONFIG_SCK_PIN;
  spi_init_struct.mosi_pin      = SPI0_CONFIG_MOSI_PIN;
  spi_init_struct.miso_pin      = SPI0_CONFIG_MISO_PIN;
  spi_init_struct.irq_priority  = SPI0_CONFIG_IRQ_PRIORITY;
  spi_init_struct.orc           = 0xFF;
  spi_init_struct.frequency     = NRF_DRV_SPI_FREQ_8M;
  spi_init_struct.mode          = NRF_DRV_SPI_MODE_0;
  spi_init_struct.bit_order     = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST;
  nrf_drv_spi_init(&SPIx.instance, &spi_init_struct, mpu9250_spi_event_handler);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9250_Init
**功能 : Init MPU9250
**輸入 : None
**輸出 : state
**使用 : state = MPU9250_Init(&MPU_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
#define MPU6500_InitRegNum 11
int8_t MPU9250_Init( MPU_ConfigTypeDef *MPUx )
{
  int8_t status = ERROR;
#ifdef _USE_MAG_AK8963
  uint8_t tmpRead[3] = {0};
#endif
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
    MPU9250_WriteReg(MPU6500_InitData[i][1], MPU6500_InitData[i][0]);
    delay_ms(1);
  }

  status = MPU9250_Check();
  if(status != SUCCESS)
    return ERROR;

  delay_ms(10);

#ifdef _USE_MAG_AK8963
  MPU9250_Mag_WriteReg(AK8963_CNTL2, 0x01);       // Reset Device
  delay_ms(1);
  MPU9250_Mag_WriteReg(AK8963_CNTL1, 0x10);       // Power-down mode
  delay_ms(1);
  MPU9250_Mag_WriteReg(AK8963_CNTL1, 0x1F);       // Fuse ROM access mode
  delay_ms(1);
  MPU9250_Mag_ReadRegs(AK8963_ASAX, tmpRead, 3);  // Read sensitivity adjustment values
  delay_ms(1);
  MPU9250_Mag_WriteReg(AK8963_CNTL1, 0x10);       // Power-down mode
  delay_ms(1);

	AK8963_ASA[0] = (int16_t)(tmpRead[0]) + 128;
	AK8963_ASA[1] = (int16_t)(tmpRead[1]) + 128;
	AK8963_ASA[2] = (int16_t)(tmpRead[2]) + 128;

  MPU9250_WriteReg(MPU6500_I2C_MST_CTRL, 0x5D);
  delay_ms(1);
  MPU9250_WriteReg(MPU6500_I2C_SLV0_ADDR, AK8963_I2C_ADDR | 0x80);
  delay_ms(1);
  MPU9250_WriteReg(MPU6500_I2C_SLV0_REG, AK8963_ST1);
  delay_ms(1);
  MPU9250_WriteReg(MPU6500_I2C_SLV0_CTRL, MPU6500_I2C_SLVx_EN | 8);
  delay_ms(1);

  MPU9250_Mag_WriteReg(AK8963_CNTL1, 0x16);       // Continuous measurement mode 2
  delay_ms(1);

	MPU9250_WriteReg(MPU6500_I2C_SLV4_CTRL, 0x09);
	delay_ms(1);
	MPU9250_WriteReg(MPU6500_I2C_MST_DELAY_CTRL, 0x81);
	delay_ms(100);
#endif

//  MPU9250_SetSpeed(SPIx_SPEED_HIGH);
  delay_ms(10);

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9250_Check
**功能 : Check Device ID
**輸入 : None
**輸出 : status
**使用 : status = MPU9250_Check();
**====================================================================================================*/
/*====================================================================================================*/
int8_t MPU9250_Check( void )
{
  uint8_t deviceID = ERROR;

  deviceID = MPU9250_ReadReg(MPU6500_WHO_AM_I);
  if(deviceID != MPU6500_Device_ID)
    return ERROR;

#ifdef _USE_MAG_AK8963
  deviceID = MPU9250_Mag_ReadReg(AK8963_WIA);
  if(deviceID != AK8963_Device_ID)
    return ERROR;
#endif

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9250_getData
**功能 : Get IMU Data
**輸入 : *dataIMU
**輸出 : None
**使用 : MPU9250_getData(dataIMU);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9250_getData( int16_t *pIMU )
{
  uint8_t tmpRead[22] = {0};

#ifdef _USE_MAG_AK8963
  MPU9250_ReadRegs(MPU6500_ACCEL_XOUT_H, tmpRead, 22);
#else
  MPU9250_ReadRegs(MPU6500_ACCEL_XOUT_H, tmpRead, 14);
#endif

  pIMU[0] = (Byte16(int16_t, tmpRead[6],  tmpRead[7]));    // Temp
  pIMU[1] = (Byte16(int16_t, tmpRead[0],  tmpRead[1]));    // Acc.X
  pIMU[2] = (Byte16(int16_t, tmpRead[2],  tmpRead[3]));    // Acc.Y
  pIMU[3] = (Byte16(int16_t, tmpRead[4],  tmpRead[5]));    // Acc.Z
  pIMU[4] = (Byte16(int16_t, tmpRead[8],  tmpRead[9]));    // Gyr.X
  pIMU[5] = (Byte16(int16_t, tmpRead[10], tmpRead[11]));   // Gyr.Y
  pIMU[6] = (Byte16(int16_t, tmpRead[12], tmpRead[13]));   // Gyr.Z
#ifdef _USE_MAG_AK8963
  if(!(tmpRead[14] & AK8963_STATUS_DRDY) || (tmpRead[14] & AK8963_STATUS_DOR) || (tmpRead[21] & AK8963_STATUS_HOFL))
    return;

  pIMU[7] = (Byte16(int16_t, tmpRead[16], tmpRead[15]));   // Mag.X
  pIMU[8] = (Byte16(int16_t, tmpRead[18], tmpRead[17]));   // Mag.Y
  pIMU[9] = (Byte16(int16_t, tmpRead[20], tmpRead[19]));   // Mag.Z

//  pIMU[7] = ((long)dataIMU[7] * AK8963_ASA[0]) >> 8;
//  pIMU[8] = ((long)dataIMU[8] * AK8963_ASA[1]) >> 8;
//  pIMU[9] = ((long)dataIMU[9] * AK8963_ASA[2]) >> 8;
#endif  
}
/*==============================================================================================*/
/*==============================================================================================*/
