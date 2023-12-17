#include"FlexConsole_Controller.hpp"
#include"ESP32Servo.h"

FlexConsole_Controller test;
uint8_t CH;
uint8_t VAL;
Servo servo1;
Servo servo2;

void setup() {
  // put your setup code here, to run once:
  test.set_serialBT("My ESP32","1234");
  Serial.begin(115200);
  pinMode(27, OUTPUT);
  pinMode(26, INPUT);

  servo1.setPeriodHertz(50);    
  servo1.attach(12, 500, 2500); 
  servo2.setPeriodHertz(50);    
  servo2.attach(14, 500, 2500); 

  digitalWrite(27, HIGH);
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

  int psd = analogRead(26);
  float dist = 1 / (float)psd * 30000;
  int dist_int = (int)dist;
  test.write_data(4,dist_int);

  switch(CH){
    case 1:
      if(VAL == 1){
        digitalWrite(27, LOW);
      }else{
        digitalWrite(27, HIGH);
      }
      break;
    case 2:
      servo1.write(VAL);
      break;
    case 3:
      servo2.write(VAL);
      break;
  }
  

  delay(50);

}
