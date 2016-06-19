/*====================================================================================================*/
/*====================================================================================================*/
#include "nrf5x_adc.h"

#include "app_util_platform.h"
/*====================================================================================================*/
/*====================================================================================================*/
static nrf_drv_adc_channel_t adc_channel_init_struct;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Config
**功能 : ADC Config
**輸入 : None
**輸出 : None
**使用 : ADC_Config();
**====================================================================================================*/
/*====================================================================================================*/
void ADC_Config( void )
{
  nrf_drv_adc_config_t adc_init_struct;

  adc_init_struct.interrupt_priority = ADC_CONFIG_IRQ_PRIORITY;
  nrf_drv_adc_init(&adc_init_struct, NULL);

  adc_channel_init_struct.config.config.ain        = NRF_ADC_CONFIG_INPUT_7;
  adc_channel_init_struct.config.config.input      = NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD; // 
  adc_channel_init_struct.config.config.reference  = NRF_ADC_CONFIG_REF_VBG;                  // 1.2V ref
  adc_channel_init_struct.config.config.resolution = NRF_ADC_CONFIG_RES_10BIT;                // 0 ~ 1023
  nrf_drv_adc_channel_enable(&adc_channel_init_struct);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Read
**功能 : ADC Read
**輸入 : channel
**輸出 : convADC
**使用 : convADC = ADC_Read(NRF_ADC_CONFIG_INPUT_7); // read AIN0
**====================================================================================================*/
/*====================================================================================================*/
int16_t ADC_Read( nrf_adc_config_input_t channel )
{
  int16_t convADC = 0;
  adc_channel_init_struct.config.config.ain = channel;
  nrf_drv_adc_sample_convert(&adc_channel_init_struct, &convADC);
  return convADC;
}
/*====================================================================================================*/
/*====================================================================================================*/
