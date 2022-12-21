#include "Gimbal.h"

EthernetServer TCPServer(RC_ROVECOMM_GIMBALBOARD_PORT);
RoveCommEthernet RoveComm;
rovecomm_packet packet;
int16_t *position;

void setup()
{
    Serial.begin(9600);

    RoveComm.begin(RC_GIMBALBOARD_FOURTHOCTET, &TCPServer, RC_ROVECOMM_GIMBALBOARD_MAC);
    delay(ROVECOMM_DELAY);

    //Attach Servo Array to Respective Pins
    servos[0].attach(R_DRIVE_SERVO);
    servos[1].attach(R_PAN_SERVO);
    servos[2].attach(R_TILT_SERVO);
    servos[3].attach(L_Drive_Servo);
    servos[4].attach(L_DRIVE_SERVO);
    servos[5].attach(L_TILT_SERVO);
    servos[6].attach(EXTRA_SERVO);

    //Servo Postions Set to Starting Positons
    servoPosition[0] = SERVO1_START;
    servoPosition[1] = SERVO2_START;
    servoPosition[2] = SERVO3_START;
    servoPosition[3] = SERVO4_START;
    servoPosition[4] = SERVO5_START;
    servoPosition[5] = SERVO6_START;
    servoPosition[6] = SERVO7_START;

    //Servo Max Values in Array
    servoMax[0] = R_DRIVE_SERVO_MAX;
    servoMax[1] = R_PAN_SERVO_MAX;
    servoMax[2] = R_TILT_SERVO_MAX;
    servoMax[3] = L_DRIVE_SERVO_MAX;
    servoMax[4] = L_PAN_SERVO_MAX;
    servoMax[5] = L_TILT_SERVO_MAX;
    servoMax[6] = EXTRA_SERVO_MAX;

    //Servo Min Values in Array
    servoMin[0] = R_DRIVE_SERVO_MIN;
    servoMin[1] = R_PAN_SERVO_MIN;
    servoMin[2] = R_TILT_SERVO_MIN;
    servoMin[3] = L_DRIVE_SERVO_MIN;
    servoMin[4] = L_PAN_SERVO_MIN;
    servoMin[5] = L_TILT_SERVO_MIN;
    servoMin[6] = EXTRA_SERVO_MIN;

    startupRoutine();
}

void loop()
{
    packet = RoveComm.read();

    switch (packet.data_id)
    {
    case RC_GIMBALBOARD_LEFTDRIVEGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(4, 0);
        break;
    case RC_GIMBALBOARD_RIGHTDRIVEGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(1, 0);
        break;
    case RC_GIMBALBOARD_LEFTMAINGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(5, 0);
        gimbalIncrement(6, 0);
        break;
    case RC_GIMBALBOARD_RIGHTMAINGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(2, 0);
        gimbalIncrement(3, 0);
        break;
    case RC_GIMBALBOARD_INITIATETESTROUTINE_DATA_ID:
        startupRoutine();
        break;
    default:
        break;
    }
}

void startupRoutine()
{
    delay(1000);
    for (int i = 0; i < 7; i++)
    {
        servos[i].write(servoMin[i]);
    }
    delay(1000);
    for (int i = 0; i < 7; i++)
    {
        servos[i].write(servoMax[i]);
    }
    delay(1000);
    for (int i = 0; i < 7; i++)
    {
        servos[i].write(servoPosition[i]);
    }
}

void dataOutput()
{
    for (int i = 0; i < 2; i++)
    {
        Serial.println(packet.data[i]);
    }
}

void gimbalIncrement(const int &servoNum, const int num)
{
    int16_t *incrementValues = (int16_t *)packet.data;
    if (abs(incrementValues[servoNum]) > IGNORE_THRESHOLD) 
    {
        servoPosition[servoNum] += incrementValues[num]; 
        if (servoPosition[servoNum] > servoMax[servoNum]) 
        {
            servoPosition[servoNum] = servoMax[servoNum];
        }
        else if (servoPosition[servoNum] < servoMin[servoNum]) 
        {
            servoPosition[servoNum] = servoMin[servoNum];
        }
    }
    servos[servoNum].write((int)servoPosition[servoNum]);
}    