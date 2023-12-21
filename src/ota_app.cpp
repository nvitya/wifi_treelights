#include <Arduino.h>

#include "board_pins.h"

#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "traces.h"

bool ota_app_initialized = false;

void ota_app_init()
{
  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  // ArduinoOTA.setHostname("myesp32");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() 
    {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      TRACE("Start updating %s\r\n", type.c_str());
    })
    .onEnd([]() 
    {
      TRACE("\r\nEnd\r\n");
    })    
    .onProgress([](unsigned int progress, unsigned int total) 
    {
      TRACE("Progress: %u%%\r\n", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) 
    {
      TRACE("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) TRACE("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) TRACE("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) TRACE("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) TRACE("Receive Failed");
      else if (error == OTA_END_ERROR) TRACE("End Failed");
      TRACE("\r\n");
    }
  );

}

void ota_app_run()
{
  if (!ota_app_initialized)
  {
    if (g_wifi_connected)
    {
      ArduinoOTA.begin();
      ota_app_initialized = true;    
    }
    return;
  }

  ArduinoOTA.handle();
}