#ifndef MY_FILE
#define MY_FILE

int drive_code();
int intake_control();
int cata_control();
int temp_check();
int left_wing_control();
int right_wing_control();
int left_flap_control();
int right_flap_control();
int hang_control();
void drive_distance(float power_in_voltage, float target_distance_in_inch, int time_limit_in_millisecond);
void push(int power, int time);
int B_teir_hang_control();


#endif