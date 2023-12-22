
#include "lights_control.h"

class TLmOff : public TLightModeBase
{
public:
  virtual void InitParams()
  {
    name = "OFF";
  }

  virtual void Step(uint32_t  astep)
  {
    for (unsigned n = 0; n < ledcnt; ++n)
    {
      uint32_t c = 0x000000;      
      leds->setPixelColor(n, c);
    }
  }
};

TLmOff  lm_off;  // this must be included only once because of this!

