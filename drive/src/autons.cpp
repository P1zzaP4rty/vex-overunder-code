#include "vex.h"
#include "custom_auto.h"

void default_constants(){
  chassis.set_drive_constants(12, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  // chassis.set_heading_constants(6, .4, 0, 1, 0);
  // chassis.set_turn_constants(12, .7, .013, 4, 15);// below 90, old

  chassis.set_turn_constants(12, 1, .019, 7, 10);// below 90

  chassis.set_swing_constants(12, 0.6, .002, 4, 15);
  chassis.set_drive_exit_conditions(1.5, 0, 2500);
  chassis.set_turn_exit_conditions(1, 25, 1000);
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
  intake_motor.spinFor(reverse, 60, deg, false);
}
//roughly 1.1deg every msec
void far_side_auton(){
  initilize();  
  chassis.set_coordinates(0, 0, 170);
  right_wing.set(true);
  push(12, 300);
  intake_motor.spin(fwd, 12, volt);
  intake_motor.spinFor(fwd, 1050, deg,false);
  right_wing.set(false);
  push(12, 650);
  task::sleep(150);
  chassis.drive_distance(-50, 168);
  intake_motor.spinFor(reverse, 1000, deg, false);
  chassis.turn_to_angle(-120, 7, 3, 0, 1000);
  task::sleep(100);
  chassis.turn_to_angle(0, 12, 25, 0, 1000);
  chassis.turn_to_angle(80);
  intake_motor.spinFor(fwd, 1600, deg, false);
  chassis.drive_distance(32, 80);
  task::sleep(225);
  chassis.drive_distance(-31);

  left_flap.set(true);
  right_flap.set(true);
  chassis.drive_distance(-16,49);
  chassis.turn_to_angle(30, 4, 3, 0, 1000);
  left_flap.set(false);
  right_flap.set(false);
  task::sleep(200);
  chassis.turn_to_angle(-128);
  left_wing.set(true);
  intake_motor.spinFor(reverse, 3000, deg, false);
  task::sleep(100);
  chassis.drive_distance(15);
  chassis.turn_to_angle(-165);
  left_wing.set(false);
  push(12, 900);
  push(-12,280);

  chassis.turn_to_angle(115, 12, 3, 0, 1000);
  intake_motor.spinFor(fwd, 1100, deg, false);
  chassis.drive_distance(50);
  task::sleep(100);
  chassis.turn_to_angle(-113, 12, 20, 0, 1000);
  intake_motor.spinFor(reverse, 300, deg, true);
  intake_motor.spinFor(fwd, 1200, deg, false);
  chassis.turn_to_angle(160, 12, 3, 0, 1000);
  push(12, 600);
  task::sleep(100);
  chassis.turn_to_angle(-90);
  intake_motor.spinFor(reverse, 2000, degrees, false);
  left_wing.set(true);
  right_wing.set(true);
  driveType(coast);
  task::sleep(100);
  push(12, 700);
  left_wing.set(false);
  right_wing.set(false);
  push(-12, 200);  
}

void close_side_auton_WP(){
  initilize();
  chassis.set_coordinates(0, 0, 100);
  intake_motor.spin(fwd, 12, volt);
  intake_motor.spinFor(fwd, 1250, deg, false);
  push(12, 950);
  chassis.drive_distance(-50, 102);
  chassis.turn_to_angle(-160, 12, 2, 0, 600);
  intake_motor.spinFor(reverse,300 ,deg, true);
  chassis.turn_to_angle(0);
  // push(12, 200);
  chassis.drive_distance(28, 40, 12,8);
  left_flap.set(true);
  task::sleep(250);
  push(-12, 300);
  left_flap.set(false);
  task::sleep(250);
  chassis.drive_distance(-15, 0, 12, 7);
  chassis.turn_to_angle(-130, 12, 20, 0, 1000);
  chassis.turn_to_angle(-165);
  intake_motor.spinFor(reverse, 4000, deg, false);
  chassis.drive_distance(31, -180, 12, 10);
  left_wing.set(true);
  right_wing.set(true);


}

void close_side_auton(){
  initilize();
  chassis.set_coordinates(0, 0, 100);
  intake_motor.spin(fwd, 12, volt);
  intake_motor.spinFor(fwd, 1250, deg, false);
  push(12, 950);
  chassis.drive_distance(-50, 102);
  chassis.turn_to_angle(-160, 12, 2, 0, 600);
  intake_motor.spinFor(reverse,300 ,deg, true);
  chassis.turn_to_angle(0);
  // push(12, 200);
  chassis.drive_distance(28, 40, 12,8);
  left_flap.set(true);
  task::sleep(250);
  push(-12, 300);
  left_flap.set(false);
  task::sleep(250);
  chassis.drive_distance(-15, 0, 12, 7);
  chassis.turn_to_angle(-130, 12, 20, 0, 1000);
  chassis.turn_to_angle(-165);
  intake_motor.spinFor(reverse, 4000, deg, false);
  chassis.drive_distance(31, -180, 12, 10);
  chassis.drive_distance(-25, -173);
  chassis.turn_to_angle(-135);
  chassis.drive_distance(-10);
  right_flap.set(true);

}


void test(){
  initilize();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_angle(45);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(135);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(180);
  chassis.turn_to_angle(0);

}









void drive_test(){
initilize();
chassis.set_coordinates(0, 0, 0);
push(12, 1000);
}
void turn_test(){
  chassis.turn_to_angle(45);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(135);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(180);
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
