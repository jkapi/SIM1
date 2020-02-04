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
	static void kill();
	
  private:
	bool readSensor(int pin);
	void findLineRight();	
	void findLineLeft();
    void isCommand();
	void handleCommand();
	void handleLine();
	void sensorsInit();
		
};

extern SIMLib Robot;
#endif