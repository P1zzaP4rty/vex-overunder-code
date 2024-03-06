#pragma once
#include "JAR-Template/drive.h"

class Drive;

extern Drive chassis;

void default_constants();

void drive_test();
void turn_test();
void swing_test();
void full_test();
void odom_test();
void tank_odom_test();
void far_side_auton();
void close_side_auton_WP();
void close_side_auton();

void push_distance(float power_in_voltage, float target_distance_in_inch, int time_limit_in_millisecond);
void push(int power, int time);

void test();
void autonomous_skills_code();



