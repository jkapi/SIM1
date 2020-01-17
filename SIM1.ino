#include "src/SIMLib/SIMLib.h"
#include "src/SIMLib/LedControl.h"

void setup() {
  // put your setup code here, to run once:
  Robot.init();
}

void loop()
{
  Robot.isCommand();
  Robot.handleCommand();
}
