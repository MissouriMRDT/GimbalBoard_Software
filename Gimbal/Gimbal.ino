#include "Gimbal.h"

EthernetServer TCPServer(RC_ROVECOMM_GIMBALBOARD_PORT);
RoveCommEthernet RoveComm;
rovecomm_packet packet;
int16_t *position;



void setup()
{
    Serial.begin(9600);

    RoveComm.begin(RC_GIMBALBOARD_FOURTHOCTET, &TCPServer, RC_ROVECOMM_GIMBALBOARD_MAC);
    Serial.println("Gimbal");

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

    pinMode(RD_BUTTON, INPUT);
    pinMode(RMP_BUTTON, INPUT);
    pinMode(RMT_BUTTON, INPUT);
    pinMode(LD_BUTTON, INPUT);
    pinMode(LMP_BUTTON, INPUT);
    pinMode(LMT_BUTTON, INPUT);
    pinMode(SPARE1_BUTTON, INPUT);
    
    startupRoutine();
}



void loop()
{
    checkButtons();

    // Parse RoveComm packets
    packet = RoveComm.read();
    switch (packet.data_id) {

        // Increment left drive gimbal by [-180, 180]
        case RC_GIMBALBOARD_LEFTDRIVEGIMBALINCREMENT_DATA_ID:
        {
            int16_t inc = ((int16_t*) packet.data)[0];
            incrementGimbal(LD_SERVO, inc);
            break;
        }

        // Increment right drive gimbal by [-180, 180]
        case RC_GIMBALBOARD_RIGHTDRIVEGIMBALINCREMENT_DATA_ID:
        {
            int16_t inc = ((int16_t*) packet.data)[0];
            incrementGimbal(RD_SERVO, inc);
            break;
        }

        // Increment left pan and tilt gimbals by [-180, 180]
        case RC_GIMBALBOARD_LEFTMAINGIMBALINCREMENT_DATA_ID:
        {
            int16_t* inc = (int16_t*) packet.data;
            incrementGimbal(LMP_SERVO, inc[0]);
            incrementGimbal(LMT_SERVO, inc[1]);
            break;
        }

        // Increment right pan and tilt gimbals by [-180, 180]
        case RC_GIMBALBOARD_RIGHTMAINGIMBALINCREMENT_DATA_ID:
        {
            int16_t* inc = (int16_t*) packet.data;
            incrementGimbal(RMP_SERVO, inc[0]);
            incrementGimbal(RMT_SERVO, inc[1]);
            break;
        }

        //
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



void incrementGimbal (const int &id, const int16_t &incrementVal)
{
    if (digitalRead(RIGHT_SWITCH)) {
        servoPosition[id] += incrementVal;
    }
    else if (digitalRead(LEFT_SWITCH)) {
        servoPosition[id] -= incrementVal;
    }
    Serial.print("ServoPosition[id]:");
    Serial.print(servoPosition[id]);
    Serial.print(" ");
    if (servoPosition[id] > servoMax[id]) {
        servoPosition[id] = servoMax[id];
    }
    else if (servoPosition[id] < servoMin[id]) {
        servoPosition[id] = servoMin[id];
    }

    Serial.print("new value:");
    Serial.println(servoPosition[id]);

    servos[id].write(servoPosition[id]);
}



void checkButtons()
{
    if (digitalRead(RD_BUTTON)) {
        Serial.println("RD_BUTTON");
        incrementGimbal(RD_SERVO, BUTTON_INC_VAL);
    }
    
    if (digitalRead(RMP_BUTTON)) {
        Serial.println("RMP_BUTTON");
        incrementGimbal(RMP_SERVO, BUTTON_INC_VAL);
    }
    
    if (digitalRead(RMT_BUTTON)) {
        Serial.println("RMT_BUTTON");
        incrementGimbal(RMT_SERVO, BUTTON_INC_VAL);
    }
    
    if (digitalRead(LD_BUTTON)) {
        Serial.println("LD_BUTTON");
        incrementGimbal(LD_SERVO, BUTTON_INC_VAL);
    }
    
    if (digitalRead(LMP_BUTTON)) {
        Serial.println("LMP_BUTTON");
        incrementGimbal(LMP_SERVO, BUTTON_INC_VAL);
    }
    
    if (digitalRead(LMT_BUTTON)) {
        Serial.println("LMT_BUTTON");
        incrementGimbal(LMT_SERVO, BUTTON_INC_VAL);
    }
    
    if (digitalRead(SPARE1_BUTTON)) {
        Serial.println("SPARE1_BUTTON");
        incrementGimbal(SPARE1_SERVO, BUTTON_INC_VAL);
    }
}
