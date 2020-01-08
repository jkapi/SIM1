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
int SIMLib::isLine(){
	
}
void SIMLib::handleLine(){

	if(readSensor(SENSOR2)){
		while(readSensor(SENSOR3)&&!readSensor(SENSOR4)){
			Motors.forward(255);
		}
		while(!readSensor(SENSOR3)&&!readSensor(SENSOR4)){
			Motors.turn(LEFT,255);
		}
	}else if(readSensor(SENSOR4)){
		while(readSensor(SENSOR3)&&!readSensor(SENSOR2)){
			Motors.forward(255);
		}
		while(!readSensor(SENSOR3)&&!readSensor(SENSOR2)){
			Motors.turn(RIGHT,255);
		}
	}else if(readSensor(SENSOR5)){
		while(readSensor(SENSOR3)){
			Motors.forward(255);
		}
		while(!readSensor(SENSOR3)){
			Motors.turn(RIGHT,255);
		}
	}else if(readSensor(SENSOR1)){
		while(readSensor(SENSOR3)){
			Motors.forward(255);
		}
		while(!readSensor(SENSOR3)){
			Motors.turn(LEFT,255);
		}	
	}else if(readSensor(SENSOR3)){
		Motors.forward(255);
	}else{
		Motors.forward(80);
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
}
