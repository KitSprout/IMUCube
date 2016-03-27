/* #include "stm32f0_usart.h" */

#ifndef __STM32F1_USART_H
#define __STM32F1_USART_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
void UART_SendByte( USART_TypeDef *USARTx, uint8_t *sendByte );
void UART_RecvByte( USART_TypeDef *USARTx, uint8_t *recvByte );
int8_t UART_RecvByteWTO( USART_TypeDef *USARTx, uint8_t *recvByte, uint32_t timeout );
void UART_SendData( USART_TypeDef *USARTx, uint8_t *sendData, uint16_t lens );
void UART_RecvData( USART_TypeDef *USARTx, uint8_t *recvData, uint16_t lens );
int8_t UART_RecvDataWTO( USART_TypeDef *USARTx, uint8_t *recvData, uint16_t lens, uint32_t timeout );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
