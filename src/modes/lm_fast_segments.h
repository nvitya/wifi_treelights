
#include "lights_control.h"

class TLmFastSegments : public TLightModeBase
{
public:
  static const unsigned  palette_cnt = 7;
  uint32_t               palette[palette_cnt] = 
  { 
    0xFFFFFF, 
    0x00FF00, 
    0xFF00FF, 
    0x0000FF, 
    0xFF0000, 
    0x00FFFF, 
    0xFFA000
  };

  TLmFastSegments(String aname) // constructor
  {
    name = aname;
    step_micros = 1000000 / 40;  // = 40 step / s
  }

  virtual void Step(uint32_t  astep)
  {
    for (unsigned n = 0; n < ledcnt; ++n)
    {
      uint32_t c = palette[n % palette_cnt];
      uint32_t m = ((n - astep) % 30);
      if (m > 2)  c = 0;

      SetPixelColor(n, c);
    }
  }
};
