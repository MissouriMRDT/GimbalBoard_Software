#include Gimbal_Code_h

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
    servoStart[0] = SERVO1_START;
    servoStart[1] = SERVO2_START;
    servoStart[2] = SERVO3_START;
    servoStart[3] = SERVO4_START;
    servoStart[4] = SERVO5_START;
    servoStart[5] = SERVO6_START;
    servoStart[6] = SERVO7_START;

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
        servos[i].write(servoStart[i]);
    }
}

void dataOutput()
{
    for (int i = 0; i < 2; i++)
    {
        Serial.println(packet.data[i]);
    }
}