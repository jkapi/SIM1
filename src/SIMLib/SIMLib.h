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
	void forward();
	void turnLeft();
	void turnRight();
	void handleLine();
	int isCommand();
	void driveParkour();
}

extern SIMLib Robot;
#endif
