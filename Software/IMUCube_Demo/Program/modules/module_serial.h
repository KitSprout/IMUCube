/* #include "module_serial.h" */

#ifndef __MODULE_SERIAL_H
#define __MODULE_SERIAL_H

#include <stdio.h>
#include "stm32f10x.h"
#include "algorithms\algorithm_string.h"
/*====================================================================================================*/
/*====================================================================================================*/
void    Serial_Config( void );

void    Serial_SendByte( uint8_t sendByte );
void    Serial_SendData( uint8_t *sendData, uint16_t lens );
void    Serial_SendStr( char *pString );
void    Serial_SendNum( StringType type, uint8_t lens, int32_t sendNum );
uint8_t Serial_RecvByte( void );
void    Serial_RecvData( uint8_t *recvData, uint16_t lens );
int8_t  Serial_RecvDataWTO( uint8_t *recvData, uint16_t lens, int32_t timeout );
void    Serial_RecvStr( char *pString );
int8_t  Serial_RecvStrWTO( char *pString, int32_t timeout );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
