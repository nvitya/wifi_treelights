
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
  String               name = "???";  // must be set  
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
  uint8_t              brightness = 50;
  uint32_t             ledcnt = 0;
  uint8_t              mode_index = 0; // this is saved

public:
  uint32_t             last_step_time = 0;
  uint32_t             scnt = 0;
  Adafruit_NeoPixel *  leds; 

  void                 Init(int aledcnt);
  void                 Run();
        
  void                 SelectMode(uint8_t aindex);

public: 
  TLightModeBase *     curmode = nullptr;
  TLightModeBase *     mode_list[MAX_MODES];
  uint8_t              mode_count = 0;
  
  void                 AddMode(TLightModeBase * amode);
  void                 SaveSettings();
  void                 LoadSettings();
};

extern TLightsControl lights;

#endif