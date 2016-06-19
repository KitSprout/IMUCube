/* #include "nrf5x_conf.h" */

#ifndef __NRF5x_CONF_H
#define __NRF5x_CONF_H

#include "nrf_drv_config.h"
/*====================================================================================================*/
/*====================================================================================================*/
//#include "nrf_adc.h"      // ADC
//#include "nrf_clock.h"    // CLOCK
//#include "nrf_ecb.h"      // ECB
//#include "nrf_egu.h"      // EGU
#include "nrf_gpio.h"       // GPIO
//#include "nrf_gpiote.h"   // GPIOTE
//#include "nrf_i2s.h"      // I2S
//#include "nrf_lpcomp.h"   // LPCOMP
//#include "nrf_nvmc.h"     // NVMC
//#include "nrf_pdm"        // PDM
//#include "nrf_ppi.h"      // PPI
//#include "nrf_pwm.h"      // PWM
//#include "nrf_qdec.h"     // QDEC
//#include "nrf_rng.h"      // RNG
//#include "nrf_rtc.h"      // RTC
//#include "nrf_saadc.h"    // SAADC
//#include "nrf_spi.h"      // SPI
//#include "nrf_spim.h"     // SPIM
//#include "nrf_spis.h"     // SPIS
//#include "nrf_temp.h"     // TEMP
//#include "nrf_timer.h"    // TIMER
//#include "nrf_twi.h"      // TWI
//#include "nrf_twim.h"     // TWIM
//#include "nrf_uart.h"     // UART
//#include "nrf_uarte.h"    // UARTE
//#include "nrf_wdt.h"      // WDT

#if (CLOCK_ENABLED == 1)
  #include "nrf_drv_clock.h"
#endif

#if (GPIOTE_ENABLED == 1)
  #include "nrf_drv_gpiote.h"
#endif

#if (TIMER0_ENABLED == 1) || (TIMER1_ENABLED == 1) || (TIMER2_ENABLED == 1) || (TIMER3_ENABLED == 1) || (TIMER4_ENABLED == 1)
  #include "nrf_drv_timer.h"
#endif

#if (RTC0_ENABLED == 1) || (RTC1_ENABLED == 1) || (RTC2_ENABLED == 1)
  #include "nrf_drv_rtc.h"
#endif

#if (RNG_ENABLED == 1)
  #include "nrf_drv_rng.h"
#endif

#if (PWM0_ENABLED == 1) || (PWM1_ENABLED == 1) || (PWM2_ENABLED == 1)
  #include "nrf_drv_pwm.h"
#endif

#if (SPI0_ENABLED == 1) || (SPI1_ENABLED == 1) || (SPI2_ENABLED == 1)
  #include "nrf_drv_spi.h"
#endif

#if (SPIS0_ENABLED == 1) || (SPIS1_ENABLED == 1) || (SPIS2_ENABLED == 1)
  #include "nrf_drv_spis.h"
#endif

#if (UART0_ENABLED == 1)
  #include "nrf_drv_uart.h"
#endif

#if (TWI0_ENABLED == 1) || (TWI1_ENABLED == 1)
  #include "nrf_drv_twi.h"
#endif

#if (TWIS0_ENABLED == 1) || (TWIS1_ENABLED == 1)
  #include "nrf_drv_twis.h"
#endif

#if (QDEC_ENABLED == 1)
  #include "nrf_drv_qdec.h"
#endif

#if (ADC_ENABLED == 1)
  #include "nrf_drv_adc.h"
#endif

#if (SAADC_ENABLED == 1)
  #include "nrf_drv_saadc.h"
#endif

#if (PDM_ENABLED == 1)
  #include "nrf_drv_pdm.h"
#endif

#if (COMP_ENABLED == 1)
  #include "nrf_drv_comp.h"
#endif

#if (LPCOMP_ENABLED == 1)
  #include "nrf_drv_lpcomp.h"
#endif

#if (WDT_ENABLED == 1)
  #include "nrf_drv_wdt.h"
#endif

#ifdef NRF52
  #if (EGU_ENABLED == 1)
    #include "nrf_drv_swi.h"
  #endif
#endif

#if (I2S_ENABLED == 1)
  #include "nrf_drv_i2s.h"
#endif
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
