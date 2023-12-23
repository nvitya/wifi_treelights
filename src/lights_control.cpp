
#include "lights_control.h"
#include "traces.h"
#include "SPIFFS.h"

TLightsControl lights;

#define PALETTE_CNT  7


void TLightModeBase::Init(uint8_t aindex, TLightsControl * actrl)
{
  index = aindex;
  pctrl = actrl;
  ledcnt = pctrl->ledcnt;  
  Setup(); // virtual function
}

void  TLightModeBase::SetPixelColor(uint16_t n, uint32_t c)
{ 
  pctrl->SetPixelColor(n, c); 
}

void  TLightModeBase::SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{ 
  pctrl->SetPixelColor(n, r, g, b); 
}

//----------------------------------------------------------------------

void TLightsControl::Init(uint32_t aledcnt, uint32_t ablankleds)
{
  fullledcnt = aledcnt;
  blankledcnt = ablankleds;  
  ledcnt = fullledcnt - blankledcnt;

  mode_count = 0;
  last_step_time = micros();

  leds = new Adafruit_NeoPixel(fullledcnt, NEOPIXEL_PIN, NEO_RGB + NEO_KHZ800);
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
  amode->Init(mode_count, this);
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
