#ifndef SIMLib_h
#define SIMLib_h

#include "Arduino.h"

class SIMLib
{
  public:
    SIMLib();
  private:
	void driveMotor(int Motor, int Speed, int Action);
	int readSensor(int pin);
	bool isLine();
	void control();
};

#endif
