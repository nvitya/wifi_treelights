#ifndef LM_FAST_SEGMENTS_H_
#define LM_FAST_SEGMENTS_H_

#include "lights_control.h"

class TLmFastSegments : public TLightModeBase
{
public:
  static const unsigned  palette_cnt = 7;

  uint32_t  palette[palette_cnt] = 
  { 
    0xFFFFFF, 
    0x00FF00, 
    0xFF00FF, 
    0x0000FF, 
    0xFF0000, 
    0x00FFFF, 
    0xFFE000
  };

  virtual void InitParams()
  {
    step_micros = 1000000 / 40;
    name = "Fast moving color segments";
  }

  virtual void Step(uint32_t  astep)
  {
    for (unsigned n = 0; n < ledcnt; ++n)
    {
      uint32_t c = palette[n % palette_cnt];
      uint32_t m = ((n - astep) % 30);
      if (m > 2)  c = 0;

      leds->setPixelColor(n, c);
    }
  }
};

TLmFastSegments  lm_fast_segments;  // this must be included only once because of this!

#endif