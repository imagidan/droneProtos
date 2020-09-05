#include <Servo.h>

Servo m1;
Servo m2;
Servo m3;
Servo m4;

int pinM1 = 5;
int pinM2 = 6;
int pinM3 = 9;
int pinM4 = 10;

void setup(){
  Serial.begin(9600);
  
  m1.attach(pinM1);
  //m2.attach(pinM2);
  //m3.attach(pinM3);
  //m4.attach(pinM4);
  delay(1);
  //m1.write(10);
  //m2.write(10);
  //m3.write(10);
  //m4.write(10);
  delay(5000);
}

void loop(){
  while (Serial.available() > 0){
    int val = Serial.parseInt();
    Serial.println(val);
    m1.write(val);
    //m2.write(val);
    //m3.write(val);
    //m4.write(val);  
  }  
}
