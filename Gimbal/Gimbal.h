#ifndef GIMBAL_H
#define GIMBAL_H

#include <RoveComm.h>
#include <RoveCommManifest.h>
#include <RoveCommPacket.h>
#include <Servo.h>

#define LMP_SERVO 1
#define LMT_SERVO 2
#define RMP_SERVO 5
#define RMT_SERVO 6
#define LD_SERVO 8
#define SPARE1 3
#define RD_SERVO 7
#define SPARE2 4

Servo leftMainPan;
Servo leftMainTilt;
Servo rightMainPan;
Servo rightMainTilt;
Servo leftDrive;
Servo spare1;
Servo rightDrive;
Servo spare2;


#define LMP_SERVO_MIN 0
#define LMP_SERVO_MAX 180
#define LMT_SERVO_MIN 0
#define LMT_SERVO_MAX 180
#define RMP_SERVO_MIN 0
#define RMP_SERVO_MAX 180
#define RMT_SERVO_MIN 0
#define RMT_SERVO_MAX 180
#define LD_SERVO_MIN 0
#define LD_SERVO_MAX 180
#define SPARE1_MIN 0
#define SPARE1_MAX 180
#define RD_SERVO_MIN 0
#define RD_SERVO_MAX 180
#define SPARE2_MIN 0
#define SPARE2_MAX 180

#define ROVECOMM_DELAY 10

#endif
