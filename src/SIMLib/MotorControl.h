#ifndef SIMLib_Motor_h
#define SIMLib_Motor_h

#include "Arduino.h"
#include "LedControl.h"

#define LEFT 1
#define RIGHT 2

#define FORWARD   1
#define BACKWARD -1
#define GO        1
#define BRAKE     0

class MotorControl
{
  public:
    MotorControl();
    void init();
    void drive(byte Motor, int Speed, int Action);
    void brake(byte Motor, bool Brake);
    void forward(int Speed = 127);
    void backward(int Speed = 127);
    void steer(int Direction, int Offset = 1024, int Speed = 127);
    void turn(int Direction, int TurnSpeed = 127);
    
  private:
    static int speedLeft;
    static int speedRight;
    
    void driveLeft(int Speed, int Action);
    void driveRight(int Speed, int Action);
};

extern MotorControl Motors;
#endif
