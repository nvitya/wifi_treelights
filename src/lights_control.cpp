
#include "lights_control.h"

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


TLightsControl lights;

#define PALETTE_CNT  7

uint32_t  palette[PALETTE_CNT] = 
{ 
  0xFFFFFF, 
  0x00FF00, 
  0xFF00FF, 
  0x0000FF, 
  0xFF0000, 
  0x00FFFF, 
  0xFFE000
};

void TLightsControl::begin()
{
  last_step_time = micros();

  leds = new Adafruit_NeoPixel(LED_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
  leds->begin();
  leds->setBrightness(50);
  leds->show();  
}

void TLightsControl::run()
{
  uint32_t t = micros();
  step_micros = mode_step_micros[mode];

  if (t - last_step_time > step_micros)
  {
    ++scnt;
    if      (1 == mode)  run_mode_1();    
    else if (2 == mode)  run_mode_2();
    else                 run_mode_0();

    leds->show();
 
    last_step_time = t;
  }
}

void TLightsControl::run_mode_0() // static palette
{
  for (unsigned n = 0; n < LED_COUNT; ++n)
  {
    uint32_t c = palette[n % PALETTE_CNT];
    //uint32_t c = 0x0000FF;
    leds->setPixelColor(n, c);
  }
}

void TLightsControl::run_mode_1() // slow moving palette
{
  for (unsigned n = 0; n < LED_COUNT; ++n)
  {
    uint32_t c = palette[(n + scnt) % PALETTE_CNT];
    leds->setPixelColor(n, c);
  }
}

void TLightsControl::run_mode_2()  // fast moving segments
{
  for (unsigned n = 0; n < LED_COUNT; ++n)
  {
    uint32_t c = palette[n % PALETTE_CNT];
    uint32_t m = ((n - scnt) % 30);
    if (m > 2)  c = 0;

    leds->setPixelColor(n, c);
  }
}

