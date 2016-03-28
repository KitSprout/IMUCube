/* #include "module_ws2812b.h" */

#ifndef __MODULE_WS2812B_H
#define __MODULE_WS2812B_H

#include "stm32f10x.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define WS2812B_COLS      (6)
#define	WS2812B_ROWS      (9)

#define WS2812B_LENS     (WS2812B_COLS * WS2812B_ROWS)

extern uint8_t  WS2812B_rgb[WS2812B_LENS][3];
/*=====================================================================================================*/
/*=====================================================================================================*/
void WS2812B_Config( void );

void WS2812B_sendPixel( uint16_t led, uint8_t r, uint8_t g, uint8_t b );
void WS2812B_sendData( uint16_t led_start, uint16_t led_end );
void WS2812B_clearAll( uint8_t r, uint8_t g, uint8_t b );

void WS2812B_testRainbow( void );
void WS2812B_testBreath( uint32_t speed );
void WS2812B_DEMO( void );

inline void WS2812B_setRGB( uint16_t led, uint8_t r, uint8_t g, uint8_t b );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
