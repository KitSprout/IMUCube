/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\nrf5x_system.h"
#include "modules\module_ws2812b.h"

#include "imuCube.h"
#include "app_timer.h"
#include "ble_advdata.h"
#include "softdevice_handler.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define APP_TIMER_PRESCALER       0   /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE   4   /**< Size of timer operation queues. */

APP_TIMER_DEF(m_leds_timer_id);

static void leds_timer_handler( void * p_context )
{
  uint32_t next_delay = 0;
  static uint8_t state = 0;

  UNUSED_PARAMETER(p_context);

  if(!state) {
    WS2812B_clearAll(0, 0, 0);
    WS2812B_clearAll(0, 0, 0);
    next_delay = 1950;  // 1950 ms
  }
  else {
    WS2812B_clearAll(16, 16, 16);
    WS2812B_clearAll(16, 16, 16);
    next_delay = 50;    // 50 ms
  }
  state = !state;

  app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(next_delay, APP_TIMER_MODE_SINGLE_SHOT), NULL);
}

void timers_init( void )
{
  uint32_t err_code;

  APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);

  // LED timer
  err_code = app_timer_create(&m_leds_timer_id, APP_TIMER_MODE_SINGLE_SHOT, leds_timer_handler);
  APP_ERROR_CHECK(err_code);
}

void timers_start( void )
{
  uint32_t err_code;

  err_code = app_timer_start(m_leds_timer_id, APP_TIMER_TICKS(1000, APP_TIMER_PRESCALER), NULL);
  APP_ERROR_CHECK(err_code);
}

#define CENTRAL_LINK_COUNT        0   /**< Number of central links used by the application. When changing this number remember to adjust the RAM settings*/
#define PERIPHERAL_LINK_COUNT     0   /**< Number of peripheral links used by the application. When changing this number remember to adjust the RAM settings*/

#define NRF_CLOCK_LFCLKSRC      {.source        = NRF_CLOCK_LF_SRC_XTAL,            \
                                 .rc_ctiv       = 0,                                \
                                 .rc_temp_ctiv  = 0,                                \
                                 .xtal_accuracy = NRF_CLOCK_LF_XTAL_ACCURACY_20_PPM}
/*====================================================================================================*/
/*====================================================================================================*/
void ble_stack_init( void )
{
  uint32_t err_code;

  nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;

  // Initialize the SoftDevice handler module.
  SOFTDEVICE_HANDLER_INIT(&clock_lf_cfg, NULL);

  ble_enable_params_t ble_enable_params;
  err_code = softdevice_enable_get_default_config(CENTRAL_LINK_COUNT, PERIPHERAL_LINK_COUNT, &ble_enable_params);
  APP_ERROR_CHECK(err_code);

  //Check the ram settings against the used number of links
  CHECK_RAM_START_ADDR(CENTRAL_LINK_COUNT,PERIPHERAL_LINK_COUNT);

  // Enable BLE stack.
  err_code = softdevice_enable(&ble_enable_params);
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
#define APP_BEACON_INFO_LENGTH          0x17                              /**< Total length of information advertised by the Beacon. */
#define APP_COMPANY_IDENTIFIER          0x0059                            /**< Company identifier for Nordic Semiconductor ASA. as per www.bluetooth.org. */

#define APP_CFG_NON_CONN_ADV_TIMEOUT    0                                 /**< Time for which the device must be advertising in non-connectable mode (in seconds). 0 disables timeout. */
#define NON_CONNECTABLE_ADV_INTERVAL    MSEC_TO_UNITS(100, UNIT_0_625_MS) /**< The advertising interval for non-connectable advertisement (100 ms). This value can vary between 100ms to 10.24s). */

static ble_gap_adv_params_t m_adv_params;

static uint8_t beaconInfo[APP_BEACON_INFO_LENGTH] =  {0};
static uint8_t beaconUUID[16]     = { 0xE2, 0xC5, 0x6D, 0xB5, 0xDF, 0xFB, 0x48, 0xD2, 0xB0, 0x60, 0xD0, 0xF5, 0xA7, 0x10, 0x96, 0xE0 };
static uint8_t beaconArbitrary[4] = { 0x00, 0x00, 0x00, 0x05 }; // { Major, Minor }
static uint8_t beaconTxPower      = 0xC3; // The Beacon's measured RSSI at 1 meter distance in dBm.

static void setBeaconInfo( uint8_t* p_beaconInfo )
{
  // Advertising Data Format
  // 
  // 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30
  // 02 01 04 1A FF 59 00 02 15 E2 C5 6D B5 DF FB 48 D2 B0 60 D0 F5 A7 10 96 E0 00 00 00 00 C3 00
  // --|--|--|--|--|-----|--|--|-----------------------------------------------|-----|-----|--|--|  
  // 02 # Number of bytes that follow in first AD structure
  // 01 # Flags AD type
  // 04 # Flags value
  // 1A # Number of bytes that follow in second (and last) AD structure
  // FF # Manufacturer specific data AD type
  // 59 00 # Company identifier code (0x0059 == Nordic Semiconductor ASA)
  // 02 # Device type (0x02 refers to Beacon)
  // 15 # Length of specific data
  // E2 C5 6D B5 DF FB 48 D2 B0 60 D0 F5 A7 10 96 E0 # Beacon proximity uuid
  // 00 00 # Major 
  // 00 00 # Minor 
  // C5 # The 2's complement of the calibrated Tx Power

  p_beaconInfo[0]  = 0x02;                      // Specifies the device type in this implementation. 0x02 refers to Beacon.
  p_beaconInfo[1]  = 0x15;                      // Length of manufacturer specific data in the advertisement.
  for(uint8_t i = 0; i < 16; i++)
    p_beaconInfo[i + 2]  = beaconUUID[i];       // Proprietary 128 bit UUID value for Beacon.
  for(uint8_t i = 0; i < 4; i++)
    p_beaconInfo[i + 18] = beaconArbitrary[i];  // Arbitrary value that can be used to distinguish between Beacons. 
  p_beaconInfo[22] = beaconTxPower;             // The Beacon's measured RSSI at 1 meter distance in dBm.
}

static void advertising_init( void )
{
  uint32_t err_code;
  uint8_t flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;

  ble_advdata_t advdata;
  ble_advdata_manuf_data_t manuf_specific_data;

  setBeaconInfo(beaconInfo);

  manuf_specific_data.company_identifier = APP_COMPANY_IDENTIFIER;
  manuf_specific_data.data.size          = APP_BEACON_INFO_LENGTH;
  manuf_specific_data.data.p_data        = (uint8_t *) beaconInfo;

  // Build and set advertising data.
  memset(&advdata, 0, sizeof(advdata));
  advdata.name_type             = BLE_ADVDATA_NO_NAME;
  advdata.flags                 = flags;
  advdata.p_manuf_specific_data = &manuf_specific_data;
  err_code = ble_advdata_set(&advdata, NULL);
  APP_ERROR_CHECK(err_code);

  // Initialize advertising parameters (used when starting advertising).
  memset(&m_adv_params, 0, sizeof(m_adv_params));
  m_adv_params.type        = BLE_GAP_ADV_TYPE_ADV_NONCONN_IND;
  m_adv_params.p_peer_addr = NULL;                             // Undirected advertisement.
  m_adv_params.fp          = BLE_GAP_ADV_FP_ANY;
  m_adv_params.interval    = NON_CONNECTABLE_ADV_INTERVAL;
  m_adv_params.timeout     = APP_CFG_NON_CONN_ADV_TIMEOUT;
}

static void advertising_start( void )
{
  uint32_t err_code;

  err_code = sd_ble_gap_adv_start(&m_adv_params);
  APP_ERROR_CHECK(err_code);
}

void ble_power_manage( void )
{
  uint32_t err_code = sd_app_evt_wait();
  APP_ERROR_CHECK(err_code);
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_Init( void )
{
  IMUCube_CKOCK_Config();
  IMUCube_GPIO_Config();
  IMUCube_WS2812B_Config();

  WS2812B_clearAll(32, 32, 32);
  delay_ms(100);
  WS2812B_clearAll(0, 0, 0);
  delay_ms(100);
  WS2812B_clearAll(32, 32, 32);
  delay_ms(100);
  WS2812B_clearAll(0, 0, 0);
  delay_ms(100);

  timers_init();
  ble_stack_init();
  advertising_init();

  timers_start();
  advertising_start();
}
/*====================================================================================================*/
/*====================================================================================================*/
void IMUCube_Loop( void )
{
  while(1) {
    ble_power_manage();
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
