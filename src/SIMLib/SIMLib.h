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
	bool readSensor(int pin);
	void findLineRight();	
	void findLineLeft();
	void handleLine();
	int isCommand();
	void sensorsInit();
};

void kill();

extern SIMLib Robot;
#endif
