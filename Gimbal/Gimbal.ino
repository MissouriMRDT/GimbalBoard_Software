#include "Gimbal.h"

Servo scoop;
int16_t servoPosition;

EthernetServer TCPServer(RC_ROVECOMM_GIMBALBOARD_PORT);
RoveCommEthernet RoveComm;
rovecomm_packet packet;

void setup()
{
  Serial.begin(115000);

  delay(ROVECOMM_DELAY);
  RoveComm.begin(RC_GIMBALBOARD_FOURTHOCTET, &TCPServer);
  delay(ROVECOMM_DELAY);

  scoop.attach(SERVO);
  scoop.write(SERVO_MIN);
}

void loop()
{
  packet = RoveComm.read();
  Serial.println(packet.data_id);

  switch(packet.data_id)
  {
    case RC_GIMBALBOARD_LEFTDRIVEGIMBALINCREMENT_DATA_ID:
      int16_t* position = (int16_t*)packet.data;
      Serial.println("Incremental: ");
      Serial.println(position[0]);
      Serial.println(position[1]);
      scoop.write(position[0]);
      break;
    default:
      break;
  }
}