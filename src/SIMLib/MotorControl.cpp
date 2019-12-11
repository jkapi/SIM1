#include "MotorControl.h"

#define M_RIGHT_DIR 12
#define M_LEFT_DIR 13
#define M_RIGHT_PWM 3
#define M_LEFT_PWM 11
#define M_RIGHT_BRK 9
#define M_LEFT_BRK 8
#define M_RIGHT_CURRENT A0
#define M_LEFT_CURRENT A1

MotorControl::MotorControl() {
    init();
}

void MotorControl::init() {
  pinMode(M_RIGHT_DIR, OUTPUT);
  pinMode(M_LEFT_DIR, OUTPUT);
  pinMode(M_RIGHT_PWM, OUTPUT);
  pinMode(M_LEFT_PWM, OUTPUT);
  pinMode(M_RIGHT_BRK, OUTPUT);
  pinMode(M_LEFT_BRK, OUTPUT);
  digitalWrite(M_RIGHT_BRK, HIGH);
  digitalWrite(M_LEFT_BRK, HIGH);
  digitalWrite(M_RIGHT_DIR, LOW);
  digitalWrite(M_LEFT_DIR, HIGH);
  analogWrite(M_RIGHT_PWM, 0);
  analogWrite(M_LEFT_PWM, 0);
}

void MotorControl::drive(byte Motor, int Speed, int Action) {
  Speed = min(255, max(-255, Speed));
  if (Speed < 0) {
    Action = -Action;
    Speed = -Speed;
  }
  if (Motor & RIGHT) {
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
  if (Motor & LEFT) {
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
}