/* #include "module_ws2812b.h" */

#ifndef __MODULE_WS2812B_H
#define __MODULE_WS2812B_H

#include "drivers\nrf5x_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define WS2812B_COLS      (6)
#define	WS2812B_ROWS      (9)
#define WS2812B_LENS      (54)    // WS2812B_COLS * WS2812B_ROWS
#define WS2812B_BUF_LENS  (1338)  // 24 * WS2812B_LENS + 42
/*====================================================================================================*/
/*====================================================================================================*/
#define WS2812B_LOGIC_H() NRF_GPIO->OUTSET = WS_PIN; \
  __ASM ( \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
  ); \
  NRF_GPIO->OUTCLR = WS_PIN;

#define WS2812B_LOGIC_L() NRF_GPIO->OUTSET = WS_PIN; \
  __ASM (  \
    " NOP\n\t"  \
  );  \
  NRF_GPIO->OUTCLR = WS_PIN;  \
  __ASM ( \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
    " NOP\n\t" \
  );
  
#define WS2812B_RESET() NRF_GPIO->OUTCLR = WS_PIN; \
  delay_us(50);
/*====================================================================================================*/
/*====================================================================================================*/
extern uint8_t WS2812B_RGB[WS2812B_LENS][3];

void WS2812B_Config( void );

void WS2812B_setRGB( uint16_t index, uint8_t r, uint8_t g, uint8_t b );
void WS2812B_sendPixel( uint16_t index, uint8_t r, uint8_t g, uint8_t b );
void WS2812B_show( void );
void WS2812B_clearAll( uint8_t r, uint8_t g, uint8_t b );

void WS2812B_testRainbow( void );
void WS2812B_testBreath( uint32_t speed );
void WS2812B_DEMO( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
