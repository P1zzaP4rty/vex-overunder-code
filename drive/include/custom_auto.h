#include "motor_group.h"




void drive_distance(float power_in_voltage, float target_distance_in_inch, int time_limit_in_millisecond){
//only called once
  int elapsed_time = 0;
  float compensation = 0;
  leftDrive.setStopping(hold);
  rightDrive.setStopping(hold);
  left_middle_motor.setPosition(0.0, degrees);//reset encoder to 0 deg, I spent 2 -3 hours figuring out how 
  float start_distance = left_middle_motor.position(deg);//^to get rid of that code but I couldn't
  float distance_traveled = fabs(left_middle_motor.position(deg) - start_distance);


  if (target_distance_in_inch <= 20){//probably this as well
    compensation = target_distance_in_inch*1.4 - target_distance_in_inch;
  }else if(20 < target_distance_in_inch && target_distance_in_inch <= 55) {
    compensation = target_distance_in_inch *1.2 - target_distance_in_inch;
  }else if (55 < target_distance_in_inch) {
    compensation = target_distance_in_inch *1.1 - target_distance_in_inch;
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
    leftDrive.spin(forward, left_power, volt);//+12 for forward, -12 for backwards
    rightDrive.spin(forward, right_power, volt);
    elapsed_time +=10;
    task::sleep(10);  
}
  leftDrive.spin(forward, 0, volt);
  rightDrive.spin(forward, 0, volt);
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
    leftDrive.spin(forward, left_power, volt);//+12 for forward, -12 for backwards
    rightDrive.spin(forward, right_power, volt);
elapsed_time += 10;
task::sleep(10);
}
leftDrive.spin(forward, 0, volt);
rightDrive.spin(forward, 0, volt);
}