#ifndef Gimbal_Code_h
#define Gimbal_Code_h

#include <Servo.h>
#include <RoveComm.h>

#define R_Drive_Servo 1
#define R_Pan_Servo 2
#define R_Tilt_Servo 3
#define L_Drive_Servo 4
#define L_Pan_Servo 5
#define L_Tilt_Servo 6
#define Extra_Servo 33

//Starting Postions
#define Servo1_START 135
#define Servo2_START 135
#define Servo3_START 135
#define Servo4_START 135
#define Servo5_START 135
#define Servo6_START 135

//Minimum and Maximum Servo Values
#define R_Drive_Servo_Min 0
#define R_Drive_Servo_Max 180
#define R_Pan_Servo_Min 0
#define R_Pan_Servo_Max 180
#define R_Tilt_Servo_Min 0
#define R_Tilt_Servo_Max 180
#define L_Drive_Servo_Min 0
#define L_Drive_Servo_Max 180
#define L_Pan_Servo_Min 0
#define L_Pan_Servo_Max 180
#define L_Tilt_Servo_Min 0
#define L_Tilt_Servo_Max 180
#define Extra_Servo_Min 0
#define Extra_Servo_Min 180

#endif