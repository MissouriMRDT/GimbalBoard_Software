#ifndef GIMBAL_H
#define GIMBAL_H

#include <RoveComm.h>
#include <RoveCommManifest.h>
#include <RoveCommPacket.h>
#include <Servo.h>

#define NUM_SERVOS 7

#define RD_SERVO        0
#define RMP_SERVO       1
#define RMT_SERVO       2
#define LD_SERVO        3
#define LMP_SERVO       4
#define LMT_SERVO       5
#define SPARE1_SERVO    6

#define RD_SERVO_PIN 1
#define RMP_SERVO_PIN 2
#define RMT_SERVO_PIN 3
#define LD_SERVO_PIN 4
#define LMP_SERVO_PIN 5
#define LMT_SERVO_PIN 6
#define SPARE1_PIN 7

Servo servos[NUM_SERVOS];
int16_t servoPosition[NUM_SERVOS];
uint16_t servoMax[NUM_SERVOS];
uint16_t servoMin[NUM_SERVOS];

//Starting Positions
#define SERVO1_START 135
#define SERVO2_START 135
#define SERVO3_START 135
#define SERVO4_START 135
#define SERVO5_START 135
#define SERVO6_START 135
#define SERVO7_START 135
#define SERVO8_START 135

//Minimum and maximum servo values
#define RD_SERVO_MIN 0
#define RD_SERVO_MAX 180
#define RMP_SERVO_MIN 0
#define RMP_SERVO_MAX 180
#define RMT_SERVO_MIN 0
#define RMT_SERVO_MAX 180
#define LD_SERVO_MIN 0
#define LD_SERVO_MAX 180
#define LMP_SERVO_MIN 0
#define LMP_SERVO_MAX 180
#define LMT_SERVO_MIN 0
#define LMT_SERVO_MAX 180
#define SPARE1_MIN 0
#define SPARE1_MAX 180

// buttons
#define RD_BUTTON       24
#define RMP_BUTTON      25
#define RMT_BUTTON      26
#define LD_BUTTON       27
#define LMP_BUTTON      28
#define LMT_BUTTON      29
#define SPARE1_BUTTON   30

#define BUTTON_INC_VAL  10

void startupRoutine();

#endif
