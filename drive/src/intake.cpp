#include "vex.h"

int intake_control(){

while (1){
  if(Controller1.ButtonA.pressing()){
    intake_motor.spin(forward, 12, volt);
  }
  else if(Controller1.ButtonB.pressing()){
    intake_motor.spin(forward, -12, volt);
  }
  else if(!((Controller1.ButtonA.pressing())&&(Controller1.ButtonB.pressing()))){
    intake_motor.spin(forward, 0, volt);
  }
  task::sleep(1);
}
  return 0;
}