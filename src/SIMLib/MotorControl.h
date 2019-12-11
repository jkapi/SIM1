#ifndef SIMLib_Motor_h
#define SIMLib_Motor_h

#include "Arduino.h"

#define LEFT 1
#define RIGHT 2

#define FORWARD   1
#define BACKWARD -1
#define GO        1
#define BREAK     0

class MotorControl
{
  public:
    MotorControl();
    void init();
    void drive(byte Motor, int Speed, int Action);
    
  private:
  
};

extern MotorControl Motors;
#endif
