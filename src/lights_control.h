
#ifndef LIGHTS_CONTROL_H_
#define LIGHTS_CONTROL_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "board_pins.h"

#define LED_COUNT     100 

class TLightsControl
{
public:
  uint32_t    step_micros = 1000000;
  uint32_t    last_step_time = 0;
  uint32_t    scnt = 0;

  void     begin();
  void     run();

public: // modes  
  uint8_t     mode = 0; // select mode here 

  uint32_t    mode_step_micros[3] = {1000000, 1000000, 1000000 / 40};

  void        run_mode_0();
  void        run_mode_1();
  void        run_mode_2();
};

extern TLightsControl lights;

#endif