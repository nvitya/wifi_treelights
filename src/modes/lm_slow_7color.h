
#include "lights_control.h"

class TLmSlow7Color : public TLightModeBase
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
    name = "Slow moving 7-Color Permutation";
  }

  virtual void Step(uint32_t  astep)
  {
    for (unsigned n = 0; n < LED_COUNT; ++n)
    {
      uint32_t c = palette[(n + astep) % palette_cnt];
      leds->setPixelColor(n, c);
    }
  }
};

TLmSlow7Color  lm_slow_7color;  // this must be included only once because of this!
