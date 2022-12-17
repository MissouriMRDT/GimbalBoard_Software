#ifndef GIMBAL_SOFTWARE_H
#define GIMBAL_SOFTWARE_H

#include <Servo.h>
#include <RoveComm.h>

#define R_DRIVE_SERVO 1 
#define R_PAN_SERVO 2
#define R_TILT_SERVO 3
#define L_DRIVE_SERVO 4
#define L_PAN_SERVO 5
#define L_TILT_SERVO 6
#define EXTRA_SERVO 33

#define NUM_SERVOS 7
Servo Servos[NUM_SERVOS];

//Starting Postions
#define SERVO1_START 135
#define SERVO2_START 135
#define SERVO3_START 135
#define SERVO4_START 135
#define SERVO5_START 135
#define SERVO6_START 135
#define SERVO7_START 135

//Minimum and Maximum Servo Values
#define R_DRIVE_SERVO_MIN 0
#define R_DRIVE_SERVO_MAX 180
#define R_PAN_SERVO_MIN 0
#define R_PAN_SERVO_MAX 180
#define R_TILT_SERVO_MIN 0
#define R_TILT_SERVO_MAX 180
#define L_DRIVE_SERVO_MIN 0
#define L_DRIVE_SERVO_MAX 180
#define L_PAN_SERVO_MIN 0
#define L_PAN_SERVO_MAX 180
#define L_TILT_SERVO_MIN 0
#define L_TILT_SERVO_MAX 180
#define EXTRA_SERVO_MIN 0
#define EXTRA_SERVO_MAX 180

#define IGNORE_THRESHOLD 2
#define ROVECOMM_DELAY 100

void startupRoutine();
void dataOutput();
void gimbalIncrement(const int & servoNum1, const int & servoNum2);

#endif