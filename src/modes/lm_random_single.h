
#include "lights_control.h"

class TLmRandomSingle : public TLightModeBase
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

  TLmRandomSingle(String aname) // constructor
  {
    name = aname;
    step_micros = 1000000 / 20;  
  }

  virtual void Step(uint32_t  astep)
  {
    uint32_t c = palette[random(palette_cnt)];
    uint32_t pos = random(ledcnt);
    for (unsigned n = 0; n < ledcnt; ++n)
    {      
      if (n == pos)
      {
        SetPixelColor(n, c);
      }
      else
      {
        SetPixelColor(n, 0);
      }
    }
  }
};
