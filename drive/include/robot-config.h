using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor left_front_motor;
extern motor left_middle_motor;
extern motor left_back_motor;
extern motor shooter_motor;
extern motor right_front_motor;
extern motor right_middle_motor;
extern motor right_back_motor;
extern motor intake_motor;
extern inertial Inertial20;
extern digital_out left_wing;
extern digital_out right_wing;
extern digital_out hang;
extern digital_out left_flap;
extern digital_out right_flap;
extern digital_out B_teir;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );