#ifndef SIMLib_h
#define SIMLib_h

#include "Arduino.h"
#include "MotorControl.h"

class SIMLib
{
  public:
    SIMLib();
    void init();
    void driveParkour();


  private:
	int readSensor(int pin);
	bool isLine();
	void handleLine();
	int isCommand();
};

extern SIMLib Robot;
#endif
