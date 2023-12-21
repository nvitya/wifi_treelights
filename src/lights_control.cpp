
#include "lights_control.h"

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
  if (aindex < mode_count)
  {
    curmode = mode_list[aindex];
    //curmode->Begin();
  }
}

void TLightsControl::AddMode(TLightModeBase * amode) 
{
  mode_list[mode_count] = amode;
  amode->Init(mode_count, leds);
  ++mode_count;
}

