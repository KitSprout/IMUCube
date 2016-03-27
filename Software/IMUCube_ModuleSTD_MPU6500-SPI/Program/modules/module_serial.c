/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f1_system.h"
#include "drivers\stm32f1_usart.h"
#include "algorithms\algorithm_string.h"

#include "module_serial.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define USARTx                USART1
#define USARTx_CLK()          RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE)
#define USARTx_IRQn           USART1_IRQn

#define USARTx_TX_PIN         GPIO_Pin_9
#define USARTx_TX_GPIO_PORT   GPIOA
#define USARTx_TX_GPIO_CLK()  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

#define USARTx_RX_PIN         GPIO_Pin_10
#define USARTx_RX_GPIO_PORT   GPIOA
#define USARTx_RX_GPIO_CLK()  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE)

#define USARTx_BAUDRATE       115200
#define USARTx_BYTESIZE       USART_WordLength_8b
#define USARTx_STOPBITS       USART_StopBits_1
#define USARTx_PARITY         USART_Parity_No
#define USARTx_HARDWARECTRL   USART_HardwareFlowControl_None
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_Config
**功能 : Serial Config
**輸入 : None
**輸出 : None
**使用 : Serial_Config();
**====================================================================================================*/
/*====================================================================================================*/
void Serial_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
//  NVIC_InitTypeDef NVIC_InitStruct;
  USART_InitTypeDef USART_InitStruct;

  /* USART Clk Init *************************************************************/
  USARTx_CLK();
  USARTx_TX_GPIO_CLK();
  USARTx_RX_GPIO_CLK();

  /* USART GPIO Config **********************************************************/
  GPIO_InitStruct.GPIO_Pin   = USARTx_TX_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;
  GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = USARTx_RX_PIN;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
  GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

  /* UART IT ********************************************************************/
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//  NVIC_InitStruct.NVIC_IRQChannel = USARTx_IRQn;
//  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStruct);

  /* UART Init ******************************************************************/
  USART_InitStruct.USART_BaudRate            = USARTx_BAUDRATE;
  USART_InitStruct.USART_WordLength          = USARTx_BYTESIZE;
  USART_InitStruct.USART_StopBits            = USARTx_STOPBITS;
  USART_InitStruct.USART_Parity              = USARTx_PARITY;
  USART_InitStruct.USART_HardwareFlowControl = USARTx_HARDWARECTRL;
  USART_InitStruct.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USARTx, &USART_InitStruct);

  /* UART Enable ****************************************************************/
//  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
  USART_Cmd(USARTx, ENABLE);
  USART_ClearFlag(USARTx, USART_FLAG_TC);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_SendByte
**功能 : Send Byte
**輸入 : sendByte
**輸出 : None
**使用 : Serial_SendByte('A');
**====================================================================================================*/
/*====================================================================================================*/
void Serial_SendByte( uint8_t sendByte )
{
  UART_SendByte(USARTx, &sendByte);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_SendData
**功能 : Send Data
**輸入 : *sendData, lens
**輸出 : None
**使用 : Serial_SendData(sendData, lens);
**====================================================================================================*/
/*====================================================================================================*/
void Serial_SendData( uint8_t *sendData, uint16_t lens )
{
  UART_SendData(USARTx, sendData, lens);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_SendStr
**功能 : Send String
**輸入 : *pString
**輸出 : None
**使用 : Serial_SendStr("Hellow World!");
**====================================================================================================*/
/*====================================================================================================*/
void Serial_SendStr( char *pString )
{
  while(*pString != '\0') {
    UART_SendByte(USARTx, (uint8_t*)pString++);
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_SendNum
**功能 : Send Number
**輸入 : type, lens, sendNum
**輸出 : None
**使用 : Serial_SendNum(Type_D, 6, 1024);
**====================================================================================================*/
/*====================================================================================================*/
void Serial_SendNum( StringType type, uint8_t lens, int32_t sendNum )
{
  char tmpStr[32] = {0};
  char *pString = tmpStr;

  num2Str(type, lens, tmpStr, sendNum);

  while(*pString != '\0') {
    UART_SendByte(USARTx, (uint8_t*)pString++);
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_RecvByte
**功能 : Recv Byte
**輸入 : *recvByte
**輸出 : None
**使用 : recvByte = Serial_RecvByte();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t Serial_RecvByte( void )
{
  uint8_t recvByte = 0;
  UART_RecvByte(USARTx, &recvByte);
  return recvByte;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_RecvData
**功能 : Recv Data
**輸入 : *recvData, lens
**輸出 : None
**使用 : Serial_RecvData(recvData, lens);
**====================================================================================================*/
/*====================================================================================================*/
void Serial_RecvData( uint8_t *recvData, uint16_t lens )
{
  UART_RecvData(USARTx, recvData, lens);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_RecvDataWTO
**功能 : Recv Data Wait Timeout
**輸入 : *recvData, lens, timeout
**輸出 : state
**使用 : state = Serial_RecvDataWTO(recvData, lens, timeout);
**====================================================================================================*/
/*====================================================================================================*/
int8_t Serial_RecvDataWTO( uint8_t *recvData, uint16_t lens, int32_t timeout )
{
  return UART_RecvDataWTO(USARTx, recvData, lens, timeout);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_RecvStr
**功能 : Recv String
**輸入 : *pString
**輸出 : None
**使用 : Serial_RecvStr(recvStr);
**====================================================================================================*/
/*====================================================================================================*/
void Serial_RecvStr( char *pString )
{
  do {
    UART_RecvByte(USARTx, (uint8_t*)pString++);
  } while(*(pString - 1) != '\0');
  *pString = '\0';
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Serial_RecvStrWTO
**功能 : Recv String Wait Timeout
**輸入 : *pString, timeout
**輸出 : state
**使用 : Serial_RecvStrWTO(recvStr, 200);
**====================================================================================================*/
/*====================================================================================================*/
int8_t Serial_RecvStrWTO( char *pString, int32_t timeout )
{
  int8_t state = ERROR;

  do {
    state = UART_RecvByteWTO(USARTx, (uint8_t*)pString++, timeout);
    if(state == ERROR)
      return ERROR;
  } while(*(pString - 1) != '\0');
  *pString = '\0';

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*/
int fputc( int ch, FILE *f )
{
  USARTx->DR = (ch & (uint16_t)0x01FF);
  while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
  return (ch);
}
int fgetc( FILE *f )
{
  while(!USART_GetFlagStatus(USARTx, USART_FLAG_RXNE));
  return (uint16_t)(USARTx->DR & (uint16_t)0x01FF);
}
/*====================================================================================================*/
/*====================================================================================================*/
