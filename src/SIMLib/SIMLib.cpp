#include "SIMLib.h"
#include "MotorControl.h"

#define NOLINE 0
#define SENSOR1 22
#define SENSOR2 23
#define SENSOR3 24
#define SENSOR4 25
#define SENSOR5 26

#define STOPBTN 21

#define NOCOMMAND 0
#define PAUZE 1
#define START 2
#define END 3

int commandState = START;
unsigned long time = 0;
SIMLib::SIMLib(){
	
}

void SIMLib::init() {
    Motors.init();
	sensorsInit();
    //attachInterrupt(digitalPinToInterrupt(STOPBTN), Kill, RISING);
}
void SIMLib::sensorsInit() {
    pinMode(SENSOR1,INPUT);
	pinMode(SENSOR2,INPUT);
    pinMode(SENSOR3,INPUT);
    pinMode(SENSOR4,INPUT);
    pinMode(SENSOR5,INPUT);

}

bool SIMLib::readSensor(int pin){
	return !digitalRead(pin);
}
void SIMLib::findLineLeft(){
	while(readSensor(SENSOR3)){
		Motors.forward(255);
	}
	while(!readSensor(SENSOR3)){
		Motors.turn(LEFT,255);
	}
}
void SIMLib::findLineRight(){
	while(readSensor(SENSOR3)){
		Motors.forward(255);
	}
	while(!readSensor(SENSOR3)){
		Motors.turn(RIGHT,255);
	}
}
void SIMLib::handleLine(){

	if(readSensor(SENSOR2)){
		findLineLeft();
	}else if(readSensor(SENSOR4)){
		findLineRight();
	}else if(readSensor(SENSOR5)){
		findLineRight();
	}else if(readSensor(SENSOR1)){
		findLineLeft();
	}else if(readSensor(SENSOR3)){
		Motors.forward(255);
	}else{
		Motors.forward(200);
	}
}

void SIMLib::Kill() {
	Motors.brake(LEFT | RIGHT, true);
    while(1) {}
}

void SIMLib::driveParkour(){
	handleLine();
}

void SIMLib::isCommand()
{
  if (digitalRead(SENSOR1) == HIGH && digitalRead(SENSOR2) == HIGH && digitalRead(SENSOR4) == HIGH && digitalRead(SENSOR5) == HIGH)
  {
    delay(500);
    if (digitalRead(SENSOR1) == HIGH && digitalRead(SENSOR2) == HIGH && digitalRead(SENSOR4) == HIGH && digitalRead(SENSOR5) == HIGH)
    {
      commandState = END;
    }
    else
    {
      commandState = PAUZE;
    }
  }
  commandState = NOCOMMAND;
}

void SIMLib::handleCommand()
{
	Serial.println(commandState);
  if (commandState == NOCOMMAND || commandState == START)
  {
    //green LED HIGH
    driveParkour();
  }
  else if (commandState == PAUZE)
  {
    //blue LED HIGH
    Motors.brake(LEFT , true);
	Motors.brake(RIGHT , true);
    delay(5000);
    commandState = NOCOMMAND;
	Motors.brake(LEFT , false);
	Motors.brake(RIGHT , false);
  }
  while (commandState == END)
  {
    //red LED HIGH
    Motors.brake(LEFT , true);
	Motors.brake(RIGHT , true);
  }
}
