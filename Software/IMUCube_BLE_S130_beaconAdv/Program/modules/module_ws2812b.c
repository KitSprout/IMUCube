/* Lava
 * 
 * WS2812B Tricolor LED (neopixel) controller
 *
 *
 * Example code:
 
	neopixel_strip_t m_strip;
	uint8_t dig_pin_num = 6;
	uint8_t leds_per_strip = 24;
	uint8_t error;
	uint8_t led_to_enable = 10;
	uint8_t red = 255;
	uint8_t green = 0;
	uint8_t blue = 159;

	neopixel_init(&m_strip, dig_pin_num, leds_per_strip);
	neopixel_clear(&m_strip);
	error = neopixel_set_color_and_show(&m_strip, led_to_enable, red, green, blue);
	if (error) {
		//led_to_enable was not within number leds_per_strip
	}
	//clear and remove strip
	neopixel_clear(&m_strip);
	neopixel_destroy(&m_strip);
 
 
 * For use with BLE stack, see information below:
	- Include in main.c
		#include "ble_radio_notification.h"
	- Call (see nrf_soc.h: NRF_RADIO_NOTIFICATION_DISTANCES and NRF_APP_PRIORITIES)
		ble_radio_notification_init(NRF_APP_PRIORITY_xxx,
									NRF_RADIO_NOTIFICATION_DISTANCE_xxx,
									your_radio_callback_handler);
	- Create 
		void your_radio_callback_handler(bool radio_active)
		{
			if (radio_active == false)
			{
				neopixel_show(&strip1);
				neopixel_show(&strip2);
				//...etc
			}
		}
	- Do not use neopixel_set_color_and_show(...) with BLE, instead use uint8_t neopixel_set_color(...);
 */

#include <stdlib.h>

#include "module_ws2812b.h"

neopixel_strip_t m_strip;

void WS2812B_Config( void )
{
  neopixel_init(&m_strip, 2, 54);
  neopixel_clear(&m_strip);
}

void WS2812B_Clear( void )
{
  neopixel_clear(&m_strip);
}

void neopixel_init(neopixel_strip_t *strip, uint8_t pin_num, uint16_t num_leds)
{
	strip->leds = (color_t*) malloc(sizeof(color_t) * num_leds);
	strip->pin_num = pin_num;
	strip->num_leds = num_leds;
	nrf_gpio_cfg_output(pin_num);
	NRF_GPIO->OUTCLR = (1UL << pin_num);
	for (int i = 0; i < num_leds; i++)
	{	
		strip->leds[i].simple.g = 0;
		strip->leds[i].simple.r = 0;
		strip->leds[i].simple.b = 0;
	}
}

void neopixel_clear(neopixel_strip_t *strip)
{
		for (int i = 0; i < strip->num_leds; i++)
		{
			strip->leds[i].simple.g = 0;
			strip->leds[i].simple.r = 0;
			strip->leds[i].simple.b = 0;
		}
			neopixel_show(strip);
}

void WS2812B_clearAll( uint8_t r, uint8_t g, uint8_t b )
{
		for (int i = 0; i < m_strip.num_leds; i++)
		{
			m_strip.leds[i].simple.g = g;
			m_strip.leds[i].simple.r = r;
			m_strip.leds[i].simple.b = b;
		}
			neopixel_show(&m_strip);
}

void neopixel_show(neopixel_strip_t *strip)
{
	const uint8_t PIN =  strip->pin_num;
	NRF_GPIO->OUTCLR = (1UL << PIN);
	delay_us(50);
			for (int i = 0; i < strip->num_leds; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if ((strip->leds[i].grb[j] & 128) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((strip->leds[i].grb[j] & 64) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((strip->leds[i].grb[j] & 32) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((strip->leds[i].grb[j] & 16) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((strip->leds[i].grb[j] & 8) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((strip->leds[i].grb[j] & 4) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((strip->leds[i].grb[j] & 2) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
					
					if ((strip->leds[i].grb[j] & 1) > 0)	{NEOPIXEL_SEND_ONE}
					else	{NEOPIXEL_SEND_ZERO}
				}
			}
}

uint8_t neopixel_set_color(neopixel_strip_t *strip, uint16_t index, uint8_t red, uint8_t green, uint8_t blue )
{
		if (index < strip->num_leds)
		{
			strip->leds[index].simple.r = red;
			strip->leds[index].simple.g = green;
			strip->leds[index].simple.b = blue;
		}
		else
				return 1;
		return 0;
}

uint8_t neopixel_set_color_and_show(neopixel_strip_t *strip, uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
		if (index < strip->num_leds)
		{
			strip->leds[index].simple.r = red;
			strip->leds[index].simple.g = green;
			strip->leds[index].simple.b = blue;
		  neopixel_show(strip);	
		}
		else
				return 1;
		return 0;
}

void neopixel_destroy(neopixel_strip_t *strip)
{
	free(strip->leds);
	strip->num_leds = 0;
	strip->pin_num = 0;
}

#define TLIG_R 4
void WS2812B_testRainbow( void )
{
  uint8_t intStageNum = 0;
  uint8_t r = TLIG_R, g = 0, b = 0;

  for(uint16_t i = 0; i < TLIG_R * 6; i++) {
    switch(intStageNum) {
      case 0: { g++; if(g == TLIG_R) { intStageNum = 1;}  break; }
      case 1: { r--; if(r == 0)      { intStageNum = 2;}  break; }
      case 2: { b++; if(b == TLIG_R) { intStageNum = 3;}  break; }
      case 3: { g--; if(g == 0)      { intStageNum = 4;}  break; }
      case 4: { r++; if(r == TLIG_R) { intStageNum = 5;}  break; }
      case 5: { b--; if(b == 0)      { intStageNum = 0;}  break; }
    }
    for(uint8_t j = 0; j < m_strip.num_leds; j++) {
      m_strip.leds[j].simple.r = r;
      m_strip.leds[j].simple.g = g;
      m_strip.leds[j].simple.b = b;
    }

    neopixel_show(&m_strip);
    delay_ms(100);
  }
}
