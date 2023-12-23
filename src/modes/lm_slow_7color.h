
#include "lights_control.h"

class TLmSlow7Color : public TLightModeBase
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

  TLmSlow7Color(String aname)  // constructor
  {
    name = aname;
  }

  virtual void Step(uint32_t astep)
  {
    for (unsigned n = 0; n < ledcnt; ++n)
    {
      uint32_t c = palette[(n + astep) % palette_cnt];
      SetPixelColor(n, c);
    }
  }
};

