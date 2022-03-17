#include "Gimbal.h"

EthernetServer TCPServer(RC_ROVECOMM_GIMBALBOARD_PORT);
RoveCommEthernet RoveComm;
rovecomm_packet packet;
int16_t* position;

void setup()
{
  Serial.begin(115000);

  delay(ROVECOMM_DELAY);
  RoveComm.begin(RC_GIMBALBOARD_FOURTHOCTET, &TCPServer, RC_ROVECOMM_GIMBALBOARD_MAC);
  delay(ROVECOMM_DELAY);

  /*leftMainPan.attach(LMP_SERVO);
  leftMainPan.write(LMP_SERVO_MIN);
  leftMainTilt.attach(LMT_SERVO);
  leftMainTilt.write(LMT_SERVO_MIN);
  rightMainPan.attach(RMP_SERVO);
  rightMainPan.write(RMP_SERVO_MIN);
  rightMainTilt.attach(RMT_SERVO);
  rightMainTilt.write(RMT_SERVO_MIN);
  leftDrive.attach(LD_SERVO);
  leftDrive.write(LD_SERVO_MIN);
  spare1.attach(SPARE1);
  spare1.write(SPARE1_MIN);
  rightDrive.attach(RD_SERVO);
  rightDrive.write(RD_SERVO_MIN);
  spare2.attach(SPARE2);
  spare2.attach(SPARE2_MIN);*/

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
  //Serial.println(packet.data_id);

  switch(packet.data_id)
  {
    case RC_GIMBALBOARD_LEFTDRIVEGIMBALINCREMENT_DATA_ID:
      /*position = (int16_t*)packet.data;
      Serial.println("Incremental: ");
      Serial.println(position[0]);
      Serial.println(position[1]);
      leftDrive.write(position[0]);*/
      gimbalIncrement(4, 6);
      break;
    case RC_GIMBALBOARD_RIGHTDRIVEGIMBALINCREMENT_DATA_ID:
      //position = (int16_t*)packet.data;
      // Serial.println("Incremental: ");
      // Serial.println(position[0]);
      // Serial.println(position[1]);
      //rightDrive.write(position[0]);
      gimbalIncrement(6, 8);
      break;
    case RC_GIMBALBOARD_LEFTMAINGIMBALINCREMENT_DATA_ID:
      // = (int16_t*)packet.data;
      // Serial.println("Incremental: ");
      // Serial.println(position[0]);
      // Serial.println(position[1]);
      //leftMainPan.write(position[0]);
      //leftMainTilt.write(position[1]);
      gimbalIncrement(0, 2);
      break;
    case RC_GIMBALBOARD_RIGHTMAINGIMBALINCREMENT_DATA_ID:
      //position = (int16_t*)packet.data;
      // Serial.println("Incremental: ");
      // Serial.println(position[0]);
      // Serial.println(position[1]);
      //rightMainPan.write(position[0]);
      //rightMainTilt.write(position[1]);
      gimbalIncrement(2, 4);
      break;
    default:
      break;
  }
}

void startupRoutine()
{
    delay(1000);
    for(int i = 0; i < 8; i++)
    {
    	servos[i].write(servoMin[i]);
    }
    delay(1000);
    for(int i = 0; i < 8; i++)
    {
    	servos[i].write(servoMax[i]);
    }
    delay(1000);
    for(int i = 0; i < 8; i++)
    {
    	servos[i].write(servoPosition[i]);
    }
    //Serial.println("Startup Routine Complete");
}

void dataOutput()
{
	for(int i = 0; i < 2; i++)
	{
		Serial.println(packet.data[i]);
	}
}

void gimbalIncrement(const int & servoNum1, const int & servoNum2)
{
    int16_t *incrementValues = (int16_t*)packet.data;

    //Serial.println("Increments");
    //Serial.println(incrementValues[0]);
    //Serial.println(incrementValues[1]);

    
    for(int i = servoNum1; i < servoNum2; i++)
    {
        if(incrementValues[i - servoNum1] > IGNORE_THRESHOLD)
        {
            servoPosition[i] += incrementValues[i - servoNum1];
            
            if(servoPosition[i] >= servoMax[i])
            {
                servoPosition[i] = servoMax[i];
            }
        }
        
        if(incrementValues[i - servoNum1] < -IGNORE_THRESHOLD)
        {
            servoPosition[i] += incrementValues[i - servoNum1];
            
            if(servoPosition[i] <= servoMin[i])
            {
                servoPosition[i] = servoMin[i]; 
            }
            //Serial.println(servoPosition[i]);
        }
        
        //Serial.println(servoPosition[i]);
        servos[i].write((int)servoPosition[i]);
        //Serial.println(servos[i].read());
    }
}