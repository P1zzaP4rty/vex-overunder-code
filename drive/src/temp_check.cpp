#include "vex.h"

int temp_check(){

forever(
    //assign temp to variable
    int LFT=left_front_motor.temperature(temperatureUnits::celsius);
    int LMT=left_middle_motor.temperature(temperatureUnits::celsius);
    int LBT=left_back_motor.temperature(temperatureUnits::celsius);
    int RFT=right_front_motor.temperature(temperatureUnits::celsius);
    int RMT=right_middle_motor.temperature(temperatureUnits::celsius);
    int RBT=right_back_motor.temperature(temperatureUnits::celsius);
    int intakeT=intake_motor.temperature(temperatureUnits::celsius);
    int shooterT=intake_motor.temperature(temperatureUnits::celsius);
    int inertial_heading = Inertial20.heading();
    //prints temp of motors, 50C+ = overheat
    Brain.Screen.setCursor(3,1); 
    Brain.Screen.clearLine();
    Brain.Screen.print("Left temp: %dC, %dC, %dC",LFT,LMT,LBT); 
    Brain.Screen.setCursor(4,1); 
    Brain.Screen.clearLine();
    Brain.Screen.print("Right temp: %dC, %dC, %dC",RFT,RMT,RBT);
    Brain.Screen.setCursor(5,1); 
    Brain.Screen.clearLine();
    Brain.Screen.print("Intake temp: %dC,",intakeT); 
    Brain.Screen.setCursor(6,1); 
    Brain.Screen.clearLine();
    Brain.Screen.print("Shooter temp: %dC,", shooterT); 
    Brain.Screen.setCursor(7,1); 
    Brain.Screen.clearLine();
    Brain.Screen.print("inertial heading: %ddeg,", inertial_heading); 
)
    return 0;
}
