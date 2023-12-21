/*
 *  file:     board_pins.cpp
 *  brief:    Board Specific Settings
 *  date:     2023-12-21
 *  authors:  nvitya
*/

#include "Arduino.h"

#include "board_pins.h"
#include "traces.h"

#include "WiFi.h"
//#include "udo_ip_comm.h"

#include "nvconfig.h"

bool          g_wifi_connected = false;

void wifi_event_handler(WiFiEvent_t event)
{
  switch(event)
  {
    case SYSTEM_EVENT_STA_GOT_IP:
      g_wifi_connected = true;
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      TRACE("WiFi lost connection\n");
      g_wifi_connected = false;
      break;
    default:
      break;
  }

  //g_udoip_comm.WifiConnected(g_wifi_connected);
}

void board_pins_init()
{
  pinMode(PIN_LED, OUTPUT);
#if defined(ARDUINO_ESP32C3_DEV)
  // turn off the ugly white led
  //pinMode(19, OUTPUT);
  //digitalWrite(19, 0);
#endif
}

void board_net_init()
{
  TCfgStb * pcfg = &g_config.data;

  IPAddress     local_IP(pcfg->ip_address.u8);
  IPAddress     gateway(pcfg->gw_address.u8);
  IPAddress     subnet(pcfg->net_mask.u8);
  IPAddress     primaryDNS(pcfg->dns.u8); //optional
  IPAddress     secondaryDNS(pcfg->dns2.u8); //optional

  g_wifi_connected = false;

  WiFi.disconnect(true);  // delete old config
  WiFi.onEvent(wifi_event_handler);  //register event handler

  if (strlen(pcfg->wifi_ssid) > 0)
  {
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
    {
      TRACE("WiFi config error!\n");
    }
    else
    {
      WiFi.begin(pcfg->wifi_ssid, pcfg->wifi_password);
    }
  }
  else
  {
    TRACE("The SSID is empty, please configure the WiFi with the net command.\n");
  }
}
