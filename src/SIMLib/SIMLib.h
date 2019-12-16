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
    void forward(int Speed, int Time);

  private:
	int readSensor(int pin);
	bool isLine();
	void handleLine();
	int isCommand();
};

extern SIMLib Robot;
#endif
