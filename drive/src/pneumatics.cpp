#include "vex.h"



int left_wing_control(){
forever(
  waitUntil(Controller1.ButtonL1.pressing());
  waitUntil(!(Controller1.ButtonL1.pressing()));
  left_wing.set(true);
  waitUntil(Controller1.ButtonL1.pressing());
  waitUntil(!(Controller1.ButtonL1.pressing()));
  left_wing.set(false);
  ) 
  return 0;
}

int right_wing_control(){
forever(
  waitUntil(Controller1.ButtonR1.pressing());
  waitUntil(!(Controller1.ButtonR1.pressing()));
  right_wing.set(true);
  waitUntil(Controller1.ButtonR1.pressing());
  waitUntil(!(Controller1.ButtonR1.pressing()));
  right_wing.set(false);
  )
  coconut_jpg
}


int left_flap_control(){
forever(
  waitUntil(Controller1.ButtonL2.pressing());
  waitUntil(!(Controller1.ButtonL2.pressing()));
  left_flap.set(true);
  waitUntil(Controller1.ButtonL2.pressing());
  waitUntil(!(Controller1.ButtonL2.pressing()));
  left_flap.set(false);
  )
  return 0;
}

int right_flap_control(){
forever(
  waitUntil(Controller1.ButtonR2.pressing());
  waitUntil(!(Controller1.ButtonR2.pressing()));
  right_flap.set(true);
  waitUntil(Controller1.ButtonR2.pressing());
  waitUntil(!(Controller1.ButtonR2.pressing()));
  right_flap.set(false);
  )
  return 0;
}

int hang_control(){
forever(
  waitUntil(Controller1.ButtonX.pressing());
  waitUntil(!(Controller1.ButtonX.pressing()));
  hang.set(true);
  waitUntil(Controller1.ButtonX.pressing());
  waitUntil(!(Controller1.ButtonX.pressing()));
  hang.set(false);
  )
  return 0;
}

int B_teir_hang_control(){
forever(
  waitUntil(Controller1.ButtonUp.pressing());
  waitUntil(!(Controller1.ButtonUp.pressing()));
  hang.set(false);
  B_teir.set(true);
  shooter_motor.spin(fwd, 12, volt);
  shooter_motor.spinFor(fwd, 1800, deg, false);
  waitUntil(Controller1.ButtonUp.pressing());
  waitUntil(!(Controller1.ButtonUp.pressing()));
  B_teir.set(false);
)
}

