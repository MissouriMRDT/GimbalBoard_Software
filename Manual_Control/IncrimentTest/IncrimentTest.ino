#include <Servo.h>

int Servo_Manual_Control_Right = 11;
int Servo_Manual_Control_Left = 12;

int Servo_1_SW = 24;
int Servo_2_SW = 25;

int servo1_Position = 40;
int servo2_Position = 40;


Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
int led = 13;

void setup() {

  servo1.attach(3);  // attaches the servo on pin 1 to the servo object
  servo2.attach(4);  // attaches the servo on pin 1 to the servo object
  pinMode(led, OUTPUT);

  startupRoutine();
}



void loop() {
  digitalWrite(led, HIGH);

  int servoStepSize = 10;

  
  while (digitalRead(Servo_Manual_Control_Right) == HIGH && digitalRead(Servo_1_SW) == HIGH){
    servo1_Position = servo1_Position + servoStepSize;
    delay(10);
    if (servo1_Position >= 180){
      servo1_Position = 180;
    }
    servo1.write(servo1_Position);
    Serial.println(servo1_Position);
    delay(10);
  }
  while (digitalRead(Servo_Manual_Control_Left) == HIGH && digitalRead(Servo_1_SW) == HIGH){
    servo1_Position = servo1_Position - servoStepSize;
    delay(10);
    if (servo1_Position <= 40){
      servo1_Position = 40;
    }
    servo1.write(servo1_Position);
    Serial.println(servo1_Position);
    delay(10);
  }
    while (digitalRead(Servo_Manual_Control_Right) == HIGH && digitalRead(Servo_2_SW) == HIGH){
    servo1_Position = servo1_Position + servoStepSize;
    delay(10);
    if (servo2_Position >= 180){
      servo2_Position = 180;
    }
    servo1.write(servo2_Position);
    Serial.println(servo2_Position);
    delay(10);
    }
  while (digitalRead(Servo_Manual_Control_Left) == HIGH && digitalRead(Servo_2_SW) == HIGH){
    servo2_Position = servo1_Position - servoStepSize;
    delay(10);
    if (servo2_Position <= 40){
      servo2_Position = 40;
    }
    servo2.write(servo2_Position);
    Serial.println(servo2_Position);
    delay(10);
  }
}
void startupRoutine(){
  servo1.write(40);
  servo2.write(40);
  delay(100);
}
