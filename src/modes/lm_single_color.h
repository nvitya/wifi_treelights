
#include "lights_control.h"

class TLmSingleColor : public TLightModeBase
{
public:
  uint32_t color;

  TLmSingleColor(String aname, uint32_t acolor) // constructor
  {
    name = aname;
    color = acolor;
    step_micros = 1000000;
  }

  virtual void Step(uint32_t  astep)
  {
    for (unsigned n = 0; n < ledcnt; ++n)
    {
      SetPixelColor(n, color);
    }
  }
};

