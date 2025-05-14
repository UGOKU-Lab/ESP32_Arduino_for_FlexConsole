#include"FlexConsole_Controller.hpp"
#include"ESP32Servo.h"
#include "MotorDriver.h"

FlexConsole_Controller test;
uint8_t CH;
uint8_t VAL;

Servo servo1;
Servo servo2;

float duty = 0.0f;

void setup() {
  // put your setup code here, to run once:
  test.set_serialBT("UGOKU One","0000");
  Serial.begin(115200);

  MotorDriver_begin();

  servo1.setPeriodHertz(50);    
  servo1.attach(14, 500, 2500); 
  servo2.setPeriodHertz(50);    
  servo2.attach(27, 500, 2500); 

  // LEDs
  pinMode(2, OUTPUT);  
  pinMode(4, OUTPUT);
  pinMode(23, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  test.read_data();
  CH = test.get_ch();
  VAL = test.get_val();
  Serial.print("Channel : ");
  Serial.println(CH);
  Serial.print("value : ");
  Serial.println(VAL);

  switch (CH) {
    case 1: // LED control
      digitalWrite(2, (VAL == 1) ? LOW : HIGH);
      break;
    case 2: // Servo 1
      servo1.write(VAL);
      break;
    case 3: // Servo 2
      servo2.write(VAL);
      break;
    case 4: // Motor 1
      duty = (VAL / 127.5f) - 1.0f;
      MotorDriver_setSpeed(MD1, duty);
      break;
    case 5: // Motor 2
      duty = (VAL / 127.5f) - 1.0f;
      MotorDriver_setSpeed(MD2, duty);
      break;
  }

  int psd = analogRead(26);
  float dist = 1 / (float)psd * 30000;
  int dist_int = (int)dist;
  test.write_data(6,dist_int);

  delay(50);

}
