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

    // attaches the servo array to the respective pins (1-8 servos are 0-7)
    servos[0].attach(LMP_SERVO);
    servos[1].attach(LMT_SERVO);
    servos[2].attach(RMP_SERVO);
    servos[3].attach(RMT_SERVO);
    servos[4].attach(LD_SERVO);
    servos[5].attach(SPARE1);
    servos[6].attach(RD_SERVO);
    servos[7].attach(SPARE2);

    // servo positions are set to starting positions
    servoPosition[0] = SERVO1_START;
    servoPosition[1] = SERVO2_START;
    servoPosition[2] = SERVO3_START;
    servoPosition[3] = SERVO4_START;
    servoPosition[4] = SERVO5_START;
    servoPosition[5] = SERVO6_START;
    servoPosition[6] = SERVO7_START;
    servoPosition[7] = SERVO8_START;

    // servo max values put in an array
    servoMax[0] = LMP_SERVO_MAX;
    servoMax[1] = LMT_SERVO_MAX;
    servoMax[2] = RMP_SERVO_MAX;
    servoMax[3] = RMT_SERVO_MAX;
    servoMax[4] = LD_SERVO_MAX;
    servoMax[5] = SPARE1_MAX;
    servoMax[6] = RD_SERVO_MAX;
    servoMax[7] = SPARE2_MAX;

    // servo min values put in an array
    servoMin[0] = LMP_SERVO_MIN;
    servoMin[1] = LMT_SERVO_MIN;
    servoMin[2] = RMP_SERVO_MIN;
    servoMin[3] = RMT_SERVO_MIN;
    servoMin[4] = LD_SERVO_MIN;
    servoMin[5] = SPARE1_MIN;
    servoMin[6] = RD_SERVO_MIN;
    servoMin[7] = SPARE2_MIN;

    startupRoutine();
}

void loop()
{
    packet = RoveComm.read();

    switch (packet.data_id)
    {
    case RC_GIMBALBOARD_LEFTDRIVEGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(4, 6);
        break;
    case RC_GIMBALBOARD_RIGHTDRIVEGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(6, 8);
        break;
    case RC_GIMBALBOARD_LEFTMAINGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(0, 2);
        break;
    case RC_GIMBALBOARD_RIGHTMAINGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(2, 4);
        break;
    default:
        break;
    }
}

void startupRoutine()
{
    delay(1000);
    for (int i = 0; i < 8; i++)
    {
        servos[i].write(servoMin[i]);
    }
    delay(1000);
    for (int i = 0; i < 8; i++)
    {
        servos[i].write(servoMax[i]);
    }
    delay(1000);
    for (int i = 0; i < 8; i++)
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

void gimbalIncrement(const int &servoNum1, const int &servoNum2)
{
    int16_t *incrementValues = (int16_t *)packet.data;

    for (int i = servoNum1; i < servoNum2; i++)
    {
        if (incrementValues[i - servoNum1] > abs(IGNORE_THRESHOLD))
        {
            servoPosition[i] += incrementValues[i - servoNum1];

            if (servoPosition[i] > servoMax[i])
            {
                servoPosition[i] = servoMax[i];
            }
            else if (servoPosition[i] < servoMin[i])
            {
                servoPosition[i] = servoMin[i];
            }
        }

        servos[i].write((int)servoPosition[i]);
    }
}