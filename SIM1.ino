#include "src/SIMLib/SIMLib.h"

void setup() {
  // put your setup code here, to run once:
  Robot.init();
}

void loop()
{
  if (millis > 500)
  {
    Robot.isCommand();
  }
  Robot.handleCommand();
}
