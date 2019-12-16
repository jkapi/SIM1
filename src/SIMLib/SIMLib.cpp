#include "SIMLib.h"
#include "MotorControl.h"

#define NOLINE 0
#define SENSOR1 22
#define SENSOR2 23
#define SENSOR3 24
#define SENSOR4 25
#define SENSOR5 26

#define NOCOMMAND 0
#define PAUZE 1
#define START 2
#define END 3

SIMLib::SIMLib(){
	
}

void SIMLib::init() {
    Motors.init();
	sensorsInit();
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
	if(readSensor(SENSOR1)){
		return SENSOR1;
	}else if(readSensor(SENSOR5)){
		return SENSOR5;
	}
	return NOLINE;
}
void SIMLib::handleLine(){
	if(isLine() == SENSOR1){
		Motors.turn(LEFT);		
	}else if(isLine() == SENSOR5){
		Motors.turn(RIGHT);
	}else{
		Motors.forward();
	}


}
int SIMLib::isCommand(){
	return NOCOMMAND;
}
void SIMLib::driveParkour(){
	handleLine();
	delay(20);
}
