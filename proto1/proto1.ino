/*
Code taken from: https://gist.github.com/vitorleal/9083802 
*/

#include <Servo.h>
 
//Create the 4 motors objects
Servo m1;
Servo m2;
Servo m3;
Servo m4;
 
//Esc pins
int pinM1 = 5;
int pinM2 = 6;
int pinM3 = 9;
int pinM4 = 10;

//Min and max pulse
int minPulseRate = 1000;
int maxPulseRate = 2000;
int throttleChangeDelay = 50;
 
//SETUP
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(500);
  
  //Init escs
  initEscs();
}
 
//LOOP
void loop() {
  // Wait for some input
  if (Serial.available() > 0) {
    
    // Read the new throttle value
    int throttle = normalizeThrottle(Serial.parseInt());
    
    // Print it out
    Serial.print("Setting throttle to: ");
    Serial.println(throttle);
    
    // Change throttle to the new value
    changeThrottle(throttle);
  }
 
}
 
//Change throttle value
void changeThrottle(int throttle) {
  int currentThrottle = readThrottle();
  
  int step = 1;
  if(throttle < currentThrottle) {
    step = -1;
  }
  
  // Slowly move to the new throttle value 
  while(currentThrottle != throttle) {
    writeTo4Motors(currentThrottle + step);
    
    currentThrottle = readThrottle();
    delay(throttleChangeDelay);
  }
}

//Read the throttle value
int readThrottle() {
  int throttle = m1.read();
  
  Serial.print("Current throttle is: ");
  Serial.print(throttle);
  Serial.println();
  
  return throttle;
}

//Change velocity of the 4 escs at the same time
void writeTo4Motors(int throttle) {
  m1.write(throttle);
  m2.write(throttle);
  m3.write(throttle);
  m4.write(throttle);
}

//Init escs
void initEscs() {
  m1.attach(pinM1, minPulseRate, maxPulseRate);
  m2.attach(pinM2, minPulseRate, maxPulseRate);
  m3.attach(pinM3, minPulseRate, maxPulseRate);
  m4.attach(pinM4, minPulseRate, maxPulseRate);
  
  //Init motors with 0 value
  writeTo4Motors(0);
}

//Start the motors
void startUpMotors() {
  writeTo4Motors(50);
}
 
// Ensure the throttle value is between 0 - 180
int normalizeThrottle(int value) {
  if(value < 0) {
    return 0;
    
  } else if(value > 180) {
    return 180;
  }
  
  return value;
}
