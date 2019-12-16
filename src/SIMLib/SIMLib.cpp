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
}

int SIMLib::readSensor(int pin){
	if (digitalRead(pin) == LOW){
		return 1;
	}
	else{
		return 0;
	}
}
bool SIMLib::isLine(){
	return NOLINE;
}
void SIMLib::handleLine(){

}
int SIMLib::isCommand(){
	return NOCOMMAND;
}
void SIMLib::driveParkour(){

}
