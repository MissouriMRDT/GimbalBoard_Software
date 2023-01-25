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
    servos[RD_SERVO].attach(RD_SERVO_PIN);
    servos[RMP_SERVO].attach(RMP_SERVO_PIN);
    servos[RMT_SERVO].attach(RMT_SERVO_PIN);
    servos[LD_SERVO].attach(LD_SERVO_PIN);
    servos[LMP_SERVO].attach(LMP_SERVO_PIN);
    servos[LMT_SERVO].attach(LMT_SERVO_PIN);
    servos[SPARE1_SERVO].attach(SPARE1_SERVO);

    // servo positions are set to starting positions
    servoPosition[RD_SERVO] = SERVO1_START;
    servoPosition[RMP_SERVO] = SERVO2_START;
    servoPosition[RMT_SERVO] = SERVO3_START;
    servoPosition[LD_SERVO] = SERVO4_START;
    servoPosition[LMP_SERVO] = SERVO5_START;
    servoPosition[LMT_SERVO] = SERVO6_START;
    servoPosition[SPARE1_SERVO] = SERVO7_START;

    // servo max values put in an array
    servoMax[RD_SERVO] = RD_SERVO_MAX;
    servoMax[RMP_SERVO] = RMP_SERVO_MAX;
    servoMax[RMT_SERVO] = RMT_SERVO_MAX;
    servoMax[LD_SERVO] = LD_SERVO_MAX;
    servoMax[LMP_SERVO] = LMP_SERVO_MAX;
    servoMax[LMT_SERVO] = LMT_SERVO_MAX;
    servoMax[SPARE1_SERVO] = SPARE1_MAX;

    // servo min values put in an array
    servoMin[RD_SERVO] = RD_SERVO_MIN;
    servoMin[RMP_SERVO] = RMP_SERVO_MIN;
    servoMin[RMT_SERVO] = RMT_SERVO_MIN;
    servoMin[LD_SERVO] = LD_SERVO_MIN;
    servoMin[LMP_SERVO] = LMP_SERVO_MIN;
    servoMin[LMT_SERVO] = LMT_SERVO_MIN;
    servoMin[SPARE1_SERVO] = SPARE1_MIN;

    setPins();
    startupRoutine();
}

void loop()
{
    buttonCheck();
    packet = RoveComm.read();

    switch (packet.data_id)
    {
    case RC_GIMBALBOARD_LEFTDRIVEGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(LD_SERVO, LD_SERVO+1);
        break;
    case RC_GIMBALBOARD_RIGHTDRIVEGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(RD_SERVO, RD_SERVO+1);
        break;
    case RC_GIMBALBOARD_LEFTMAINGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(LMP_SERVO, LMT_SERVO+1);
        break;
    case RC_GIMBALBOARD_RIGHTMAINGIMBALINCREMENT_DATA_ID:
        gimbalIncrement(RMP_SERVO, RMT_SERVO+1);
        break;
    default:
        break;
    }
}

void startupRoutine()
{
    delay(1000);
    for (int i = 0; i < NUM_SERVOS; i++)
    {
        servos[i].write(servoMin[i]);
    }
    delay(1000);
    for (int i = 0; i < NUM_SERVOS; i++)
    {
        servos[i].write(servoMax[i]);
    }
    delay(1000);
    for (int i = 0; i < NUM_SERVOS; i++)
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
        if (abs(incrementValues[i - servoNum1]) > IGNORE_THRESHOLD)
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

void setPins()
{
    pinMode(RD_BUTTON, INPUT);
    pinMode(RMP_BUTTON, INPUT);
    pinMode(RMT_BUTTON, INPUT);
    pinMode(LD_BUTTON, INPUT);
    pinMode(LMP_BUTTON, INPUT);
    pinMode(LMT_BUTTON, INPUT);
    pinMode(SPARE1_BUTTON, INPUT);
}

void buttonCheck()
{
    if (digitalRead(RD_BUTTON))
    {
        gimbalIncrement(RD_SERVO, RD_SERVO+1);
    }
    if (digitalRead(RMP_SERVO))
    {
        gimbalIncrement(RMP_SERVO, RMP_SERVO+1);
    }
    if (digitalRead(RMT_SERVO))
    {
        gimbalIncrement(RMT_SERVO, RMT_SERVO+1);
    }
    if (digitalRead(LD_SERVO))
    {
        gimbalIncrement(LD_SERVO, LD_SERVO+1);
    }
    if (digitalRead(LMP_SERVO))
    {
        gimbalIncrement(LMP_SERVO, LMP_SERVO+1);
    }
    if (digitalRead(LMT_SERVO))
    {
        gimbalIncrement(LMT_SERVO, LMT_SERVO+1);
    }
    if (digitalRead(SPARE1_SERVO))
    {
        gimbalIncrement(SPARE1_SERVO, SPARE1_SERVO+1);
    }
}