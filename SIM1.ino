#include "src/SIMLib/SIMLib.h"

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  Robot.init();
}

void loop()
{
 
  
    Robot.isCommand();
 
  Robot.handleCommand();
}
