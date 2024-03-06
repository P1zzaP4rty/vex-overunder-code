#include "vex.h"


int cata_control(){

shooter_motor.spin(forward, 0, volt);
forever(
  waitUntil(Controller1.ButtonY.pressing());
  waitUntil(!(Controller1.ButtonY.pressing()));
  shooter_motor.spin(forward, 12, volt);
  waitUntil(Controller1.ButtonY.pressing());
  waitUntil(!(Controller1.ButtonY.pressing()));
  shooter_motor.spin(forward, 0, volt);
)
return 0;
}