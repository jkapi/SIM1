#ifndef SIMLib_h
#define SIMLib_h

#include "Arduino.h"
#include "MotorControl.h"

class SIMLib
{
  public:
    SIMLib();
    void init();
    void isCommand();
	void handleCommand();
	
  private:
	bool readSensor(int pin);
	void findLineRight();	
	void findLineLeft();
    void driveParkour();
	void handleLine();
	void sensorsInit();
	void Kill();	
};

extern SIMLib Robot;
#endif
