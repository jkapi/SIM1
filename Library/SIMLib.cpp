#include "SIMLib.h"

#define NOLINE 0
#define SENSOR01 1
#define SENSOR02 2
#define SENSOR03 3
#define SENSOR04 4
#define SENSOR05 5

#define NOCOMMAND 0
#define PAUZE 1
#define START 2
#define END 3

SIMLib::SIMLib(){
	
}
void SIMLib::driveMotor(int Motor, int Speed, int Action){
}
int SIMLib::readSensor(int pin){
	return 0;
}
int SIMLib::isLine(){
	return NOLINE;
}
void SIMLib::forward(){
	
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