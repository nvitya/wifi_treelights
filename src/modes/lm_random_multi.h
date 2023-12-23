
#include "lights_control.h"

class TLmRandomMulti : public TLightModeBase
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

  uint32_t   active_count = 1;

  static const unsigned max_active_leds = 16;
  uint32_t   led_color[max_active_leds];
  uint16_t   led_pos[max_active_leds];

  TLmRandomMulti(String aname, uint32_t acnt, uint32_t afps) // constructor
  {
    name = aname;
    active_count = acnt;
    step_micros = 1000000 / afps;  
  }

  virtual void Step(uint32_t  astep)
  {
    uint32_t n, a;
    for (a = 0; a < active_count; ++a)
    {
      led_color[a] = palette[random(palette_cnt)];
      led_pos[a] = random(ledcnt);
    }
    for (unsigned n = 0; n < ledcnt; ++n)
    {
      unsigned c = 0;
      for (a = 0; a < active_count; ++a)
      {
        if (n == led_pos[a])
        {
          c = led_color[a];
          break;
        }
      }
      SetPixelColor(n, c);
    }
  }
};
