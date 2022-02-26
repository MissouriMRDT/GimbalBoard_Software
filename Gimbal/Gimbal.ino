#include "Gimbal.h"

EthernetServer TCPServer(RC_ROVECOMM_GIMBALBOARD_PORT);
RoveCommEthernet RoveComm;
rovecomm_packet packet;
int16_t* position;

void setup()
{
  Serial.begin(115000);

  delay(ROVECOMM_DELAY);
  RoveComm.begin(RC_GIMBALBOARD_FOURTHOCTET, &TCPServer);
  delay(ROVECOMM_DELAY);

  leftMainPan.attach(LMP_SERVO);
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
  spare2.attach(SPARE2_MIN);
}

void loop()
{
  packet = RoveComm.read();
  //Serial.println(packet.data_id);

  switch(packet.data_id)
  {
    case RC_GIMBALBOARD_LEFTDRIVEGIMBALINCREMENT_DATA_ID:
      position = (int16_t*)packet.data;
      Serial.println("Incremental: ");
      Serial.println(position[0]);
      Serial.println(position[1]);
      leftDrive.write(position[0]);
      break;
    case RC_GIMBALBOARD_RIGHTDRIVEGIMBALINCREMENT_DATA_ID:
      position = (int16_t*)packet.data;
      // Serial.println("Incremental: ");
      // Serial.println(position[0]);
      // Serial.println(position[1]);
      rightDrive.write(position[0]);
      break;
    case RC_GIMBALBOARD_LEFTMAINGIMBALINCREMENT_DATA_ID:
      position = (int16_t*)packet.data;
      // Serial.println("Incremental: ");
      // Serial.println(position[0]);
      // Serial.println(position[1]);
      leftMainPan.write(position[0]);
      leftMainTilt.write(position[1]);
      break;
    case RC_GIMBALBOARD_RIGHTMAINGIMBALINCREMENT_DATA_ID:
      position = (int16_t*)packet.data;
      // Serial.println("Incremental: ");
      // Serial.println(position[0]);
      // Serial.println(position[1]);
      rightMainPan.write(position[0]);
      rightMainTilt.write(position[1]);
      break;
    default:
      break;
  }
}
