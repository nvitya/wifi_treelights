
#ifndef LIGHTS_CONTROL_H_
#define LIGHTS_CONTROL_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "board_pins.h"

class TLightModeBase
{
public:
  virtual ~TLightModeBase() {}  // some compilers require virtual desctructor

  uint8_t              index = 0;
  const char *         name = "???";  // must be set  
  uint32_t             step_micros = 1000000;
  Adafruit_NeoPixel *  leds = nullptr; 
  uint32_t             ledcnt = 0;

  void          Init(uint8_t aindex, Adafruit_NeoPixel *  aleds);
  virtual void  InitParams() { }
  virtual void  Step(uint32_t  astep)   { }
};

class TLightsControl
{
public:
  uint8_t     brightness = 50;
  uint32_t    ledcnt = 0;
  uint8_t     mode = 0; // select mode here 

public:
  uint32_t    step_micros = 1000000;
  uint32_t    last_step_time = 0;
  uint32_t    scnt = 0;
  Adafruit_NeoPixel *  leds; // = 

  void        Init(int aledcnt);
  void        Run();

  void        SelectMode(uint8_t aindex);

public: // modes  

  TLightModeBase *  curmode = nullptr;
  TLightModeBase *  mode_list[MAX_MODES];
  uint8_t           mode_count = 0;

  void              AddMode(TLightModeBase * amode);

  uint32_t    mode_step_micros[3] = {1000000, 1000000, 1000000 / 40};

  void        run_mode_0();
  void        run_mode_1();
  void        run_mode_2();
};

extern TLightsControl lights;

#endif