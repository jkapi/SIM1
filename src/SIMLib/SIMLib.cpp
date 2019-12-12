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
	return 0;
}
bool SIMLib::isLine(){
	return NOLINE;
}

void SIMLib::forward(int Speed, int Time){
	Motors.drive(RIGHT | LEFT, Speed, FORWARD);
	delay(Time);
	Motors.drive(RIGHT | LEFT, 0, BRAKE);
}
void SIMLib::turnLeft(){
	
}
void SIMLib::turnRight(){
	
}
void SIMLib::handleLine(){

}
int SIMLib::isCommand(){
	return NOCOMMAND;
}
void SIMLib::driveParkour(){

}