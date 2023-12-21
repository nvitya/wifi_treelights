/*
 * board.h
 *
 *  Created on: May 27, 2023
 *      Author: vitya
 */

#ifndef SRC_BOARD_PINS_H_
#define SRC_BOARD_PINS_H_

#define  SCOPE_DATA_BUFFER_SIZE  (32 * 1024)

#define NEOPIXEL_PIN    0

#if defined(ARDUINO_LOLIN_C3_MINI)
  #define PIN_LED        7
#elif defined(ARDUINO_ESP32C3_WROOM02)
  #define PIN_LED        9
#elif defined(ARDUINO_ESP32C3_DEV)
  #define PIN_LED       18
  #define PIN_LED2      19
#elif defined(ARDUINO_LOLIN_S2_MINI)
  #define PIN_LED       15
#elif defined(ARDUINO_ESP32S3_DEV)
  #define PIN_LED        2
#else
  #error "unknown board!"
#endif

extern IPAddress     local_IP;
extern IPAddress     gateway;
extern IPAddress     subnet;
extern IPAddress     primaryDNS;
extern IPAddress     secondaryDNS;

extern char          wifi_ssid[64];
extern char          wifi_password[64];

extern bool          g_wifi_connected;

void board_net_init();
void board_pins_init();

#endif /* SRC_BOARD_PINS_H_ */
