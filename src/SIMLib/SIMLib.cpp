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

unsigned long time = 0;
SIMLib::SIMLib(){
	
}

void SIMLib::init() {
    Motors.init();
	sensorsInit();
	
    attachInterrupt(digitalPinToInterrupt(STOPBTN), kill, RISING);
	if (digitalRead(STOPBTN)) {
		kill();
	}
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
	if (readSensor(SENSOR3)){
		Motors.forward(255);
	}
	while(!readSensor(SENSOR3)){
		Motors.turn(LEFT,255);
	}
}
void SIMLib::findLineRight(){
	if(readSensor(SENSOR3)){
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

void kill() {
	Motors.brake(LEFT | RIGHT, true);
    while(1) {}
}

int SIMLib::isCommand(){
	return NOCOMMAND;
}
void SIMLib::driveParkour(){
	handleLine();
<<<<<<< Updated upstream
}
=======
}

void SIMLib::isCommand()
{
	const bool stoptest = false;
	if (millis() > 2) {
	  if (readSensor(SENSOR1) && readSensor(SENSOR2) && readSensor(SENSOR4) && readSensor(SENSOR5))
	  {
		  Motors.forward(110);
		  delay(350);
		  if (stoptest || (readSensor(SENSOR1) && readSensor(SENSOR2) && readSensor(SENSOR4) && readSensor(SENSOR5)))
		  {
			  delay(375);
			  commandState = END;
		  }
		  else
		  {
			  commandState = PAUZE;
		  }
	  }
	} else {
		// kijk of je op het startteken zit of niet, hoeft wss niet eens)
	}
}

void SIMLib::handleCommand()
{

  if (commandState == NOCOMMAND || commandState == START)
  {
    //green LED HIGH
    driveParkour();
  }
  else if (commandState == PAUZE)
  {
    //blue LED HIGH
    Motors.brake(LEFT | RIGHT, true);
    delay(5000);
    commandState = NOCOMMAND;
    Motors.brake(LEFT | RIGHT, false);
  }
  while (commandState == END)
  {
    //red LED HIGH
	kill();
  }
}
>>>>>>> Stashed changes
