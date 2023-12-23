
#include "lights_control.h"
#include "modes/light_modes.h"

// the modes can be included only once !
#include "modes/lm_single_color.h"
#include "modes/lm_static_7color.h"
#include "modes/lm_slow_7color.h"
#include "modes/lm_fast_segments.h"
#include "modes/lm_random_single.h"
#include "modes/lm_random_multi.h"

void light_modes_init()
{
  lights.AddMode( new TLmStatic7Color(  "Static 7-color Palette"        ));
  lights.AddMode( new TLmSlow7Color(    "Slow changing 7-color Palette" ));
  lights.AddMode( new TLmFastSegments(  "Fast moving color segments"    ));
  lights.AddMode( new TLmRandomMulti(   "Random 1x / 30 FPS", 1, 30     ));
  lights.AddMode( new TLmRandomMulti(   "Random 3x / 60 FPS", 3, 60     ));
  lights.AddMode( new TLmSingleColor(   "OFF",     0x000000             ));
  lights.AddMode( new TLmSingleColor(   "RED",     0xFF0000             ));
  lights.AddMode( new TLmSingleColor(   "GREEN",   0x00FF00             ));
  lights.AddMode( new TLmSingleColor(   "BLUE",    0x0000FF             ));
  lights.AddMode( new TLmSingleColor(   "WHITE",   0xFFFFFF             ));
  lights.AddMode( new TLmSingleColor(   "YELLOW",  0xFFA000             ));
}