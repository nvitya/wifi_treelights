
#include "lights_control.h"
#include "traces.h"
#include "SPIFFS.h"

TLightsControl lights;

#define PALETTE_CNT  7


void TLightModeBase::Init(uint8_t aindex, Adafruit_NeoPixel * aleds)
{
  index = aindex;
  leds = aleds;
  ledcnt = leds->numPixels();
  InitParams();  
}

//----------------------------------------------------------------------

void TLightsControl::Init(int aledcnt)
{
  ledcnt = aledcnt;
  mode_count = 0;

  last_step_time = micros();

  leds = new Adafruit_NeoPixel(ledcnt, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
  leds->begin();
  leds->setBrightness(brightness);
  leds->show();  
}

void TLightsControl::Run()
{
  if (!curmode)
  {
    return;
  }

  uint32_t t = micros();
  if (t - last_step_time > curmode->step_micros)
  {
    ++scnt;
    curmode->Step(scnt);
    leds->show();
    last_step_time = t;
  }
}

void TLightsControl::SelectMode(uint8_t aindex)
{
  // warning: mode_count can not be 0 !
  if (aindex >= mode_count)  aindex = mode_count - 1;

  mode_index = aindex;
  curmode = mode_list[aindex];
  scnt = 0;
  curmode->Step(0);
  leds->show();
  last_step_time = micros();
}

void TLightsControl::AddMode(TLightModeBase * amode) 
{
  mode_list[mode_count] = amode;
  amode->Init(mode_count, leds);
  ++mode_count;
}

void TLightsControl::SaveSettings() 
{
  File file = SPIFFS.open("/light_mode.bin", FILE_WRITE);
  if (!file)
  {
    TRACE("Error writing mode file!\r\n");
    return;
  }

  if (!file.write((const uint8_t *)&mode_index, sizeof(mode_index)))
  {
    TRACE("Mode save failed!\r\n");
  }

  file.close();
}

void TLightsControl::LoadSettings() 
{
  File file = SPIFFS.open("/light_mode.bin", FILE_READ);
  if (file)
  {
    if (!file.read((uint8_t *)&mode_index, sizeof(mode_index)))
    {
      TRACE("Error reading mode!\r\n");
    }
    file.close();
  }
  else
  {
    TRACE("Error reading mode file!\r\n");
  }

  SelectMode(mode_index);
}
