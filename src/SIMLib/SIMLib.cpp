#include "SIMLib.h"
#include "MotorControl.h"
#include "LedControl.h"

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
#define ERROR 4

unsigned long time = 0;
int commandState = START;
SIMLib::SIMLib(){
	
}

void SIMLib::init() {
    Motors.init();
	sensorsInit();
    Leds.init();
    
    // Add interrupt to the button on front, so that if something happens with it, the robot will stop.
    attachInterrupt(digitalPinToInterrupt(STOPBTN), kill, CHANGE);
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
    pinMode(STOPBTN,INPUT);
}

bool SIMLib::readSensor(int pin){
	return !digitalRead(pin); // Output of sensor is inverse of what it sees
}
void SIMLib::findLineLeft(){
	if (readSensor(SENSOR3)){
		Motors.forward(255);
	}
    
    // If the sensors on the other side are on, go straight
    if (readSensor(SENSOR4) || readSensor(SENSOR5)) return;
    
    
    bool skippo = false;
    if (readSensor(SENSOR1) && readSensor(SENSOR2) && readSensor(SENSOR3) && !readSensor(SENSOR5)) { // if sharp turn is detected
        Motors.turn(LEFT, 255);
        for (int i = 0; i < 12; i++){
            delay(25);
            // in case it was actually a pause mark and we weren't going straight
            if (readSensor(SENSOR5) && readSensor(SENSOR4)) return; // stop turning and start detecting!
        }
        skippo = true;
    }
    
    // if we're off line, turn
	if(readSensor(SENSOR3) == LOW){
		Motors.turn(LEFT,255);
        
        // it could be that we were turning to the wrong direction, if so; try turning in the other directions
        if (readSensor(SENSOR5) && !readSensor(SENSOR1) && !skippo) {
            while(!readSensor(SENSOR3)){
                Motors.turn(RIGHT,255);
            }
        }
	}
}
void SIMLib::findLineRight(){
	if(readSensor(SENSOR3)){
		Motors.forward(255);
	}
    
    // If the sensors on the other side are on, go straight
    if (readSensor(SENSOR2) || readSensor(SENSOR1)) return;
    bool skippo = false;
    if (readSensor(SENSOR5) && readSensor(SENSOR4) && readSensor(SENSOR3) && !readSensor(SENSOR1)) { // if sharp turn is detected
        Motors.turn(RIGHT, 255);
        for (int i = 0; i < 12; i++){
            delay(25);
            // in case it was actually a pause mark and we weren't going straight
            if (readSensor(SENSOR1) && readSensor(SENSOR2)) return; // stop turning and start detecting!
        }
        skippo = true;
    }
    
    // if we're off line, turn
	if(readSensor(SENSOR3) == LOW){
		Motors.turn(RIGHT,255);
        // it could be that we were turning to the wrong direction, if so; try turning in the other directions
        if (readSensor(SENSOR1) && !readSensor(SENSOR5) && !skippo) {
            while(!readSensor(SENSOR3)){
                Motors.turn(LEFT,255);
            }
        }
	}
}

void SIMLib::handleLine(){
    static int dir = FORWARD; // initialize to FORWARD
    
    // doing it this way, because if there's no sensor detected, it probably needs to do what it did.
	if(readSensor(SENSOR2)){
		dir = LEFT;
	}else if(readSensor(SENSOR4)){
		dir = RIGHT;
	}else if(readSensor(SENSOR5)){
		dir = RIGHT;
	}else if(readSensor(SENSOR1)){
		dir = LEFT;
	}else if(readSensor(SENSOR3)){
		dir = FORWARD;
	}
    
    switch(dir) {
        case LEFT: findLineLeft(); break;
        case RIGHT: findLineRight(); break;
        case FORWARD: Motors.forward(255); break;
    }
}

void SIMLib::kill() {
    noInterrupts();
    Motors.brake(LEFT | RIGHT, true);
    Leds.error();
    while(1) {/*Do nothing*/}
}

void SIMLib::driveParkour() {
  Robot.isCommand();
  Robot.handleCommand();
}


void SIMLib::isCommand() {
	const bool stoptest = false;
	if (millis() > 2500) { // Ignore pause or brake in the first 2.5s that you're probably on the start sign
	  if (readSensor(SENSOR1) && readSensor(SENSOR5)) // && readSensor(SENSOR2) && readSensor(SENSOR4)
	  {
		  Motors.forward(100);
		  delay(250);
		  if (stoptest || (readSensor(SENSOR1) && readSensor(SENSOR5))) // && readSensor(SENSOR2) && readSensor(SENSOR4)
		  {
			  delay(300);
			  commandState = END;
		  }
		  else
		  {
			  commandState = PAUZE;
		  }
	  }
	}
}

void SIMLib::handleCommand()
{
  if (commandState == NOCOMMAND || commandState == START)
  {
    handleLine();
  }
  else if (commandState == PAUZE)
  {
    Motors.brake(LEFT | RIGHT, true);
    Leds.pause();
    Motors.brake(LEFT | RIGHT, false);
    commandState = NOCOMMAND;
  }
  if (commandState == ERROR) {
      kill();
  }
  while (commandState == END)
  {
	Motors.brake(LEFT | RIGHT, true);
    Leds.stop();
  }
}