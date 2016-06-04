/* #include "imuCube_bsp.h" */

#ifndef __IMUCUBE_BSP_H
#define __IMUCUBE_BSP_H

/*====================================================================================================*/
/*====================================================================================================*/
#define BUZ           (0)
#define BUZ_Set()     __GPIO_SET(BUZ)
#define BUZ_Reset()   __GPIO_RST(BUZ)
#define BUZ_Toggle()  __GPIO_TOG(BUZ)

#define MOT           (24)
#define MOT_Set()     __GPIO_SET(MOT)
#define MOT_Reset()   __GPIO_RST(MOT)
#define MOT_Toggle()  __GPIO_TOG(MOT)

#define KEY           (23)
#define KEY_Read()    (__GPIO_READ(KEY) == 1)
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_CKOCK_Config( void );
void IMUCube_GPIO_Config( void );
void IMUCube_UART_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
