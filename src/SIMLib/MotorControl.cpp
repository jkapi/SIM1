#include "MotorControl.h"

// Used pins for the motor shield. Shall always be fixed with this shield, so I included it in the library
#define M_RIGHT_DIR 12
#define M_LEFT_DIR 13
#define M_RIGHT_PWM 3
#define M_LEFT_PWM 11
#define M_RIGHT_BRK 9
#define M_LEFT_BRK 8
#define M_RIGHT_CURRENT A0
#define M_LEFT_CURRENT A1

MotorControl::MotorControl() {
    // Initialize on instancing. Probably never used, but still.
    init();
}


void MotorControl::init() {
  pinMode(M_RIGHT_DIR, OUTPUT);
  pinMode(M_LEFT_DIR, OUTPUT);
  pinMode(M_RIGHT_PWM, OUTPUT);
  pinMode(M_LEFT_PWM, OUTPUT);
  pinMode(M_RIGHT_BRK, OUTPUT);
  pinMode(M_LEFT_BRK, OUTPUT);
  
  // Break on both motors
  digitalWrite(M_RIGHT_BRK, HIGH);
  digitalWrite(M_LEFT_BRK, HIGH);
  
  // Set direction to forward
  digitalWrite(M_RIGHT_DIR, LOW);
  digitalWrite(M_LEFT_DIR, HIGH);
  
  // Set speed to standing still
  analogWrite(M_RIGHT_PWM, 0);
  analogWrite(M_LEFT_PWM, 0);
}

void MotorControl::driveLeft(int Speed, int Action) {
    switch (Action) {
      case FORWARD:
        digitalWrite(M_LEFT_DIR, HIGH);
        analogWrite(M_LEFT_PWM, Speed);
        digitalWrite(M_LEFT_BRK, LOW);
        break;
      case BACKWARD:
        digitalWrite(M_LEFT_DIR, LOW);
        analogWrite(M_LEFT_PWM, Speed);
        digitalWrite(M_LEFT_BRK, LOW);
        break;
      default:
        analogWrite(M_LEFT_PWM, 0);
        digitalWrite(M_LEFT_BRK, HIGH);
    }
    
}

void MotorControl::driveRight(int Speed, int Action) {
    switch (Action) {
      case FORWARD:
        digitalWrite(M_RIGHT_DIR, LOW);
        analogWrite(M_RIGHT_PWM, Speed);
        digitalWrite(M_RIGHT_BRK, LOW);
        break;
      case BACKWARD:
        digitalWrite(M_RIGHT_DIR, HIGH);
        analogWrite(M_RIGHT_PWM, Speed);
        digitalWrite(M_RIGHT_BRK, LOW);
        break;
      default:
        analogWrite(M_RIGHT_PWM, 0);
        digitalWrite(M_RIGHT_BRK, HIGH);
    }
}

/* MotorControl.drive(byte Motor, int Speed, int Action)
 * Motor = RIGHT | LEFT     <- both are possible at the same time
 * Speed = driving speed from 0 to 255, negative values are also possible to go in reverse direction
 * Action = FORWARD | BACKWARD | GO | BRAKE
 */
void MotorControl::drive(byte Motor, int Speed, int Action) {
  // Keep the speed within acceptable range
  Speed = min(255, max(-255, Speed));
  
  // Allow negative speed for easy direction changing
  if (Speed < 0) {
    Action = -Action;
    Speed = -Speed;
  }
  
  if (Motor & RIGHT) {
      driveRight(Speed, Action);
  }
  
  if (Motor & LEFT) {
      driveLeft(Speed, Action);
  }
}

/* MotorControl.brake(byte Motor,  int Brake)
 * Motor = RIGHT | LEFT     <- both are possible at the same time
 * Brake = If a motor is breaking or not, defaults to true
 */
void MotorControl::brake(byte Motor, bool Brake) {
    if (Motor == RIGHT) {
        digitalWrite(M_RIGHT_BRK, Brake);
    }
    if (Motor == LEFT) {
        digitalWrite(M_LEFT_BRK, Brake);
    }
}
/* MotorControl.forward(int Speed)
 * Tell both motors to go forward with speed Speed. Default speed is 50%
 */
void MotorControl::forward(int Speed = 127) {
  Speed = min(255, max(0, Speed));
  
  driveRight(Speed, FORWARD);
  driveLeft(Speed, FORWARD);
}

/* MotorControl.backward(int Speed)
 * Tell both motors to go backward with speed Speed. Default speed is 50%
 */
void MotorControl::backward(int Speed = 127) {
  Speed = min(255, max(0, Speed));
  
  driveRight(Speed, BACKWARD);
  driveLeft(Speed, BACKWARD);
}
/* MotorControl.steer(int Direction, int Offset, int Speed)
 * Steer into a direction with base speed Speed and offset being the speed offset from the base speed.
 * For example, Direction RIGHT, Speed 127 and Offset 3 makes the Left motor turn with speed 127+3 and
 * the right on with speed 127-3
 * Direction = LEFT | RIGHT
 * Offset = The offset from the base speed, defaults to high enough to keep one motor still and the other *          at full speed
 * Speed = Base motor speed, defaults to 50%
 *
 */
void MotorControl::steer(int Direction, int Offset = 1024, int Speed = 127) {
    int wheelDir = FORWARD;
    if (Speed < 0) {
        Speed = -Speed;
        wheelDir = BACKWARD;
    }
    Speed = min(255, Speed);
    
    int speedLeft;
    int speedRight;
    
    if (Direction == LEFT) {
        speedLeft  = Speed - Offset;
        speedRight = Speed + Offset;
    } else {
        speedLeft  = Speed + Offset;
        speedRight = Speed - Offset;
    }
    
    speedLeft = min(255, max(0, speedLeft));
    speedRight = min(255, max(0, speedRight));
    
    driveLeft(speedLeft, wheelDir);
    driveRight(speedRight, wheelDir);
}

void MotorControl::turn(int Direction, int Speed = 127) {
    if (Speed < 0) {
        Speed = -Speed;
        if (Direction == RIGHT) {
            Direction == LEFT;
        } else {
            Direction == RIGHT;
        }
    }
    
    Speed = min(255, max(0, Speed));
    
    if (Direction == LEFT) {
        driveLeft(Speed, BACKWARD);
        driveRight(Speed, FORWARD);
    } else {
        driveLeft(Speed, FORWARD);
        driveRight(Speed, BACKWARD);
    }
}