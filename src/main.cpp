#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "WiFi.h"
#include "SPIFFS.h"

#include "cmdline_app.h"
#include "ota_app.h"
#include "board_pins.h"
#include "traces.h"

//#include "wifi_secret.h"

#include "lights_control.h"

uint32_t  g_last_hb = 0;
uint32_t  g_hbcounter = 0;

void setup() 
{
  board_pins_init();
  traces_init();

  digitalWrite(PIN_LED, 1);
  delay(500);  // this delay is for the platformio IDE, to switch the UART to console

  TRACE("\n\n--------------------------------\n");
  TRACE("Initializing file system...\r\n");
  if (SPIFFS.begin(true))  // formatOnFail = true
  {
    TRACE("SPIFFS initialized.\r\n");
  }
  else
  {
    TRACE("Error initializing SPIFFS!\r\n");
  }

  g_config.Init(); // also loads the confiugration

  g_cmdline.Init();
  g_cmdline.ShowNetAdapterInfo();
  g_cmdline.ShowNetInfo(nullptr, 0);

  board_net_init();

  TRACE("\r\n");

  g_cmdline.WritePrompt();

  lights.begin();
}


void IRAM_ATTR loop() 
{
  uint32_t t = micros();

  lights.run();

  g_cmdline.Run();
  ota_app_run();

  if (t - g_last_hb > 1000000 / 2)
  {
    ++g_hbcounter;
    //digitalWrite(PIN_LED, g_hbcounter & 1);

    //Serial.printf("hbcnt=%u\r\n", g_hbcnt);

    g_last_hb = t;
  }

  taskYIELD();
}                     
