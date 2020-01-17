#include "src/SIMLib/SIMLib.h"

void setup() {

  // put your setup code here, to run once:
  Robot.init();
}

<<<<<<< Updated upstream
void loop() {
  // put your main code here, to run repeatedly:
  Robot.driveParkour();
=======
void loop()
{
  Robot.isCommand();
  Robot.handleCommand();
>>>>>>> Stashed changes
}
