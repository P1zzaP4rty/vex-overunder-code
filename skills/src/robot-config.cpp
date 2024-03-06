#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor left_front_motor = motor(PORT12, ratio6_1, true);
motor left_middle_motor = motor(PORT13, ratio6_1, true);
motor left_back_motor = motor(PORT14, ratio6_1, true);
motor shooter_motor = motor(PORT15, ratio36_1, false);
motor right_front_motor = motor(PORT16, ratio6_1, false);
motor right_middle_motor = motor(PORT17, ratio6_1, false);
motor right_back_motor = motor(PORT18, ratio6_1, false);
motor intake_motor = motor(PORT2, ratio18_1, false);
inertial Inertial20 = inertial(PORT10);
digital_out left_wing = digital_out(Brain.ThreeWirePort.H);
digital_out right_wing = digital_out(Brain.ThreeWirePort.G);
digital_out hang = digital_out(Brain.ThreeWirePort.F);
digital_out left_flap = digital_out(Brain.ThreeWirePort.E);
digital_out right_flap = digital_out(Brain.ThreeWirePort.D);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}