#include "vex.h"


void default_constants(){
  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  // chassis.set_heading_constants(6, .055, 0, 2.5, 0);

  chassis.set_heading_constants(6, .4, 0, 1, 0); //auton one

  // chassis.set_heading_constants(7, 4, 0.2, 1, 15);

  chassis.set_turn_constants(12, .6, .045, 4.5, 15);// below 90

  chassis.set_swing_constants(12, 0.6, .02, 4, 15);
  chassis.set_drive_exit_conditions(1.5, 0, 2500);
  chassis.set_turn_exit_conditions(1, 100, 1000);
  chassis.set_swing_exit_conditions(1, 50, 1000);
}



void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 12;
  chassis.drive_settle_error = 3;
}
void initilize(){
  odom_constants();
  intake_motor.setBrake(brake);
  intake_motor.setMaxTorque(100, pct);
  intake_motor.spin(forward);
  intake_motor.setVelocity(100, pct);
  intake_motor.spinFor(reverse, 360, deg, false);
}

void far_side_auton(){
  initilize();  
  chassis.set_coordinates(0, 0, 0);
  
}

void close_side_auton_WP(){
  initilize();
  chassis.set_coordinates(0, 0, 0);
}

void close_side_auton(){
  initilize();
  chassis.set_coordinates(0, 0, 0);
}












void drive_test(){
  initilize();
    chassis.set_coordinates(0, 0, 0);
    push(12, 1500);

}
void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}
void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}
void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}
void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}
void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}


motor_group left_Drive = motor_group(left_front_motor, left_middle_motor, left_back_motor);
motor_group right_Drive = motor_group(right_front_motor, right_middle_motor, right_back_motor);


void push_distance(float power_in_voltage, float target_distance_in_inch, int time_limit_in_millisecond){
//only called once
  int elapsed_time = 0;
  float compensation = 0;
  left_Drive.setStopping(hold);
  right_Drive.setStopping(hold);
  left_middle_motor.setPosition(0.0, degrees);//reset encoder to 0 deg, I spent 2 -3 hours figuring out how 
  float start_distance = left_middle_motor.position(deg);//^to get rid of that code but I couldn't
  float distance_traveled = fabs(left_middle_motor.position(deg) - start_distance);


  if (target_distance_in_inch < 40){//probably this as well
    compensation = target_distance_in_inch / 3;//change this
  }else {
    compensation = target_distance_in_inch / 4;//change this
  }


  
  float distance_from_target = distance_traveled - (target_distance_in_inch - compensation);
  float target_heading = Inertial20.heading(degrees);
//gets called repeatedly, for updating values
while(distance_from_target <= 0 && elapsed_time < time_limit_in_millisecond){
  
    distance_traveled = fabs(fabs(left_middle_motor.position(deg))*0.6/360.0*M_PI*3.25 - start_distance);
    distance_from_target = distance_traveled - (target_distance_in_inch - compensation);
    float current_heading = Inertial20.heading(degrees);
    float angle = target_heading - current_heading;
      while(!(angle >= -180 && angle < 180)) {
    if( angle < -180 ) { angle += 360; }
    if(angle >= 180) { angle -= 360; }
  }
    float left_power = power_in_voltage + angle*1;
    float right_power = power_in_voltage;
    double maxInputMag = fmax(fabs(left_power),fabs(right_power));
    if (maxInputMag > 12){
      left_power /=maxInputMag;
      right_power /=maxInputMag;
      left_power *=12;
      right_power *=12;
    }
    left_Drive.spin(forward, left_power, volt);//+12 for forward, -12 for backwards
    right_Drive.spin(forward, right_power, volt);
    elapsed_time +=10;
    task::sleep(10);  
}
  left_Drive.spin(forward, 0, volt);
  right_Drive.spin(forward, 0, volt);
}

void push (int power, int time){

int elapsed_time = 0;
float target_heading = Inertial20.heading(degrees);

while (elapsed_time < time){

//gets called repeatedly, for updating values

    float current_heading = Inertial20.heading(degrees);
    float angle = target_heading - current_heading;
      while(!(angle >= -180 && angle < 180)) {
    if( angle < -180 ) { angle += 360; }
    if(angle >= 180) { angle -= 360; }
  }
    float left_power = power + angle*1;
    float right_power = power;
    double maxInputMag = fmax(fabs(left_power),fabs(right_power));
    if (maxInputMag > 12){
      left_power /=maxInputMag;
      right_power /=maxInputMag;
      left_power *=12;
      right_power *=12;
    }
    left_Drive.spin(forward, left_power, volt);//+12 for forward, -12 for backwards
    right_Drive.spin(forward, right_power, volt);
elapsed_time += 10;
task::sleep(10);
}
left_Drive.spin(forward, 0, volt);
right_Drive.spin(forward, 0, volt);
}

void test(){

}
////////////////////////////////////////////
////////////////////////////////////////////

void autonomous_skills_code(){
  initilize();
  chassis.set_coordinates(0, 0, -135);
  chassis.drive_distance(-23);
  // chassis.set_heading_constants(6, .055, 0, 2.5, 0);
  chassis.drive_distance(-8, -90);
  // chassis.drive_distance(-8, -110, 12, 4, 1.5, 0, 1000,  1.5, 0, 10, 0, .055, 0, 2.5, 0);  
  push(-12, 600);
  // chassis.set_heading_constants(6, .2, 0, 1, 0);
  chassis.drive_distance(10, -90);  
  chassis.turn_to_angle(165);
  right_flap.set(true);
  shooter_motor.spin(forward, 11, volt);
  intake_motor.spin(forward, -12, volt);
  waitUntil(Controller1.ButtonX.pressing() || time_elapsed >= 30000);
  shooter_motor.spin(forward, 0, volt);
  right_flap.set(false);


  chassis.turn_to_angle(-145);
  chassis.drive_distance(20);
  chassis.right_swing_to_angle(180);

  chassis.drive_distance(55, 180);
  left_wing.set(true);
  right_wing.set(true);
  chassis.drive_distance(15);
  chassis.drive_distance(25, 140);
  push(12, 250);
  chassis.drive_distance(18, 110);
  chassis.turn_to_angle(110);
  left_wing.set(false);
  right_wing.set(false);
  task::sleep(100);
  push(12, 900);
  // chassis.turn_to_angle(100, 12, 3, 0, 1000);
  push(-12, 300);
  task::sleep(200);
  chassis.turn_to_angle(110, 12, 3, 50, 1000);
  task::sleep(50);
  push(12, 900);
  chassis.drive_distance(-13);
  // chassis.drive_distance(10, 90);
  // push(12, 700);
  chassis.turn_to_angle(-170);

  left_flap.set(true);
  right_flap.set(true);
  chassis.drive_distance(-10);
  chassis.drive_distance(-25, -140);
  chassis.right_swing_to_angle(-5);
  push(-12, 900);
  chassis.drive_distance(10, -8);
  chassis.turn_to_angle(-8, 12, 2, 0, 1000);
  push(-12, 500);
  left_flap.set(false);
  right_flap.set(false);

  chassis.turn_to_angle(0, 12, 2, 0, 1000);
  chassis.drive_distance(23);
  chassis.left_swing_to_angle(85);
  left_wing.set(true);
  chassis.drive_distance(10, 85);
  chassis.turn_to_angle(-173);
  left_wing.set(true);
  right_wing.set(true);
  task::sleep(250);
  push(12, 800);
  chassis.drive_distance(-15);
  chassis.turn_to_angle(180, 12, 2, 0, 1000);
  task::sleep(200);
  push(12, 600);
  left_wing.set(false);
  right_wing.set(false);
  chassis.drive_distance(-23);
  chassis.turn_to_angle(-75);
  left_flap.set(true);
  right_flap.set(true);
  chassis.drive_distance(-60);
  chassis.right_swing_to_angle(45);
  right_flap.set(false);
  push(-12, 300);
  chassis.right_swing_to_angle(60);
  push(-12, 700);
  chassis.drive_distance(18, 60);
  chassis.turn_to_angle(60, 12, 2, 0, 1000);
  task::sleep(150);
  push(-12, 700);
  chassis.drive_distance(18, 60);
  chassis.turn_to_angle(60, 12, 2, 0, 1000);
  task::sleep(150);
  push(-12, 700);
  chassis.drive_distance(18);




  // chassis.drive_distance(-35);
  // chassis.turn_to_angle(-70);
  // left_flap.set(true);
  // right_flap.set(true);
  // chassis.drive_distance(-50);










}