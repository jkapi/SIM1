#ifndef SIMLib_h
#define SIMLib_h

#include "Arduino.h"
#include "MotorControl.h"

class SIMLib
{
  public:
    SIMLib();
    void init();
  private:
	int readSensor(int pin);
	bool isLine();
};

extern SIMLib Robot;
#endif
