
#include "lights_control.h"
#include "modes/light_modes.h"

// the modes can be included only once !
#include "modes/lm_static_7color.h"
#include "modes/lm_slow_7color.h"
#include "modes/lm_fast_segments.h"
#include "modes/lm_off.h"

void light_modes_init()
{
  lights.AddMode(&lm_static_7color);
  lights.AddMode(&lm_slow_7color);
  lights.AddMode(&lm_fast_segments);
  lights.AddMode(&lm_off);
}