#ifndef SIMLib_Leds_h
#define SIMLib_Leds_h

#include "Arduino.h"
#include <FastLED.h>

#define PIN_LEDR   28
#define PIN_LEDL   27

class LedControl
{
  public:
    LedControl();
    void init();
    void both(int pos, CRGB color);
    void flood(CRGB color);
    void error();
    void showSpeedLeft(int speed);
    void showSpeedRight(int speed);
    void pause();
    void clear();
    void stop();
    
  private:
};

extern LedControl Leds;
#endif
