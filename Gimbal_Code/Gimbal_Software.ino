#include Gimbal_Code_h

void setup()
{
    Serial.begin(9600);

    RoveComm.begin(RC_GIMBALBOARD_FOURTHOCTET, &TCPServer, RC_ROVECOMM_GIMBALBOARD_MAC);
    delay(ROVECOMM_DELAY);

    //Attach Servo Array to Respective Pins
    servos[0].attach(R_Drive_Servo);
    servos[1].attach(R_Pan_Servo);
    servos[2].attach(R_Tilt_Servo);
    servos[3].attach(L_Drive_Servo);
    servos[4].attach(L_Pan_Servo);
    servos[5].attach(L_Tilt_Servo);
    servos[6].attach(Extra_Servo);

    //Servo Postions Set to Starting Positons
    Servo_Start[0] = Servo1_START;
    Servo_Start[1] = Servo2_START;
    Servo_Start[2] = Servo3_START;
    Servo_Start[3] = Servo4_START;
    Servo_Start[4] = Servo5_START;
    Servo_Start[5] = Servo6_START;
    Servo_Start[6] = Extra_Servo;
}