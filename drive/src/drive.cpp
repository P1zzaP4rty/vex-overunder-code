#include "vex.h"
#include "cstdlib"
// #include "motor_group.h"

using namespace std;

motor_group left_Drive = motor_group(left_front_motor, left_middle_motor, left_back_motor);
motor_group right_Drive = motor_group(right_front_motor, right_middle_motor, right_back_motor);

int drive_code(){

while (1){
  double A3 = Controller1.Axis3.position();//setting up a3 a4 for convenience
  double A4 = Controller1.Axis4.position();

  double deadband = 1;
  double powerL;
  double powerR;

  if (fabs(A3)<deadband){//deadband incase joistick doesn't return to absolute origin
    A3=0;                //prevents movement
  }
  if (fabs(A4)<deadband){
    A4=0;
  }

  //expenential drive
  powerL = (A3*fabs(A3)/100+A4*fabs(A4)/100)*0.12;
  powerR = (A3*fabs(A3)/100-A4*fabs(A4)/100)*0.12;

  //set max input
  double maxInputMag = fmax(fabs(powerL),fabs(powerR));
  if (maxInputMag > 12){
    powerL /=maxInputMag;
    powerR /=maxInputMag;
    powerL *=12;
    powerR *=12;
  }        

  left_Drive.spin(forward, powerL, volt);
  right_Drive.spin(forward, powerR, volt);
  task::sleep(1);
}
return 0;
}
