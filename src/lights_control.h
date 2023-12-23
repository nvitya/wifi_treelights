
#ifndef LIGHTS_CONTROL_H_
#define LIGHTS_CONTROL_H_

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "board_pins.h"

class TLightsControl;

class TLightModeBase
{
public:
  uint8_t              index = 0;
  String               name = "???";  // must be set in the constructor
  uint32_t             step_micros = 1000000;

  TLightsControl *     pctrl = nullptr; 
  uint32_t             ledcnt = 0;

  virtual              ~TLightModeBase() {}  // some compilers require virtual desctructor
  void                 Init(uint8_t aindex, TLightsControl * actrl);
  void                 SetPixelColor(uint16_t n, uint32_t c);
  void                 SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);

  virtual void         Setup()                 { }  // virtual function for one time preparation
  virtual void         Step(uint32_t  astep)   { }  // this virtual function must be implemented
};

class TLightsControl
{
public:
  uint8_t              brightness = 50;
  uint32_t             fullledcnt = 0;
  uint32_t             ledcnt = 0;
  uint32_t             blankledcnt = 0;
  uint8_t              mode_index = 0; // this is saved

public:
  void                 Init(uint32_t aledcnt, uint32_t ablankleds);
  void                 Run();        
  void                 SelectMode(uint8_t aindex);

  inline void          SetPixelColor(uint16_t n, uint32_t c) 
  { 
    leds->setPixelColor(n + blankledcnt, c); 
  }

  inline void          SetPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
  { 
    leds->setPixelColor(n + blankledcnt, r, g, b); 
  }

public: 
  TLightModeBase *     curmode = nullptr;
  TLightModeBase *     mode_list[MAX_MODES];
  uint8_t              mode_count = 0;
  
  void                 AddMode(TLightModeBase * amode);
  void                 SaveSettings();
  void                 LoadSettings();

protected:
  uint32_t             last_step_time = 0;
  uint32_t             scnt = 0;
  Adafruit_NeoPixel *  leds = nullptr; 

};

extern TLightsControl lights;

#endif