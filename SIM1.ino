#include "src/SIMLib/SIMLib.h"

void setup() {
  // put your setup code here, to run once:
  Robot.init();
  Motors.drive(RIGHT | LEFT, 255, FORWARD);
  delay(1000);
  Motors.drive(RIGHT | LEFT, 0, BREAK);
}

void loop() {
  // put your main code here, to run repeatedly:

}
