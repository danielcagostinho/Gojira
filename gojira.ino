#include <Ultrasonic.h>

// motor vars
const unsigned int enablePinL = 11; 
const unsigned int enablePinR = 10;
const unsigned int in1PinL = 12;
const unsigned int in2PinL = 13;
const unsigned int in1PinR = 9;
const unsigned int in2PinR = 8;
const unsigned int maxSpeed = 248;
unsigned int speed;
unsigned int starting_speed = 0.6*maxSpeed;

// QRD
const unsigned int QrdThreshold = 200;
const unsigned int QrdPin0 = A5;
const unsigned int QrdPin1 = A1;
unsigned int QrdValue0;
unsigned int QrdValue1;
boolean white;
 
const unsigned int TxPin = 3;
const unsigned int RxPin = 4;

Ultrasonic midSonar(TxPin, RxPin);

boolean enemySpotted;
boolean forwardL = true;
boolean forwardR = true;

enum State {
  SEARCHING,
  WAITING,
  SONIC_TRIPPED};

int trip_value;

State currentState;
State previousState;

void setup() {
// motor
pinMode(in1PinL, OUTPUT);
pinMode(in2PinL, OUTPUT); 
pinMode(in1PinR, OUTPUT); 
pinMode(in2PinR, OUTPUT); 
pinMode(enablePinL, OUTPUT);
pinMode(enablePinR, OUTPUT);

// QRD
 pinMode(QrdPin0, INPUT);
 pinMode(QrdPin1, INPUT);

// ULTRASONIC
pinMode(TxPin, OUTPUT);
pinMode(RxPin, INPUT);

speed = starting_speed;

// Test code
  Serial.begin(9600);
  Serial.println("+-------------------------------------------+");
  Serial.println("|            QRD Sensor Readings            |");
  Serial.println("+-------------------------------------------+");
previousState = WAITING;
currentState = WAITING;
delay(5000);
}

void loop() {
  switch (currentState){
    case WAITING:
      previousState = WAITING;
      currentState = SEARCHING;
      break;
      
    case SEARCHING:
      Serial.print("SEARCHING");
      trip_value = isQrdTripped();
      moveAwayFromBoundary(trip_value);
      // forward motion may interfere with pivot search
      creepLeft();
        delay(1000);
      forward();
      delay(250);
      if (ultrasense() == true) {
        previousState = SEARCHING;
        currentState = SONIC_TRIPPED;
        break;
      }
      break;
      
    case SONIC_TRIPPED:
      if (previousState != SONIC_TRIPPED) {
        bufferMotor(); 
      }
      
      Serial.print("SONIC TRIPPED");
      //trip_value = isQrdTripped();
      //moveAwayFromBoundary(trip_value);
      pivotRight();
      delay(150);
      
      forward();
      delay(500);
      if (ultrasense() == false) {
        previousState = SONIC_TRIPPED;
        currentState = SEARCHING;
        break;
      }
       
      break;
      
  }
}

bool ultrasense() {
  int distance = midSonar.read(CM);
  Serial.print("Front Distance: ");
  Serial.println(distance);
  if (distance < 100) {
    return true;
  } else {
    return false;
  }
}

void bufferMotor(){
   analogWrite(enablePinL, 0);
   digitalWrite(in1PinL, 1);
   digitalWrite(in2PinL, 0);
   analogWrite(enablePinR, 0);
   digitalWrite(in1PinR, 1);
   digitalWrite(in2PinR, 0);
   delay(300);
}

void pivotLeft(){
  Serial.print("PIVOT LEFT");
  speed = 0.6*maxSpeed;
  forwardL = false;
  forwardR = true;
  setMotor(speed, forwardL, forwardR);
}

void pivotRight(){
  Serial.print("PIVOT RIGHT");
  speed = 0.6*maxSpeed;
  forwardL = true;
  forwardR = false;
  setMotor(speed, forwardL, forwardR);
}

void creepLeft(){
  speed = 0.4*maxSpeed;
  forwardL = false;
  forwardR = true;
  setMotor(speed, forwardL, forwardR);
}

void reverse(){
  Serial.print("REVERSE");
  speed = maxSpeed;
  forwardL = false;
  forwardR = false;
  setMotor(speed, forwardL, forwardR);
}

void forward() {
  Serial.print("FORWARD");
  speed = maxSpeed;
  forwardL = true;
  forwardR = true;
  setMotor(speed, forwardL, forwardR);
}

void moveAwayFromBoundary(int qrdNum){ // 1 for left 0 for right
  switch(qrdNum){
    case 1:
      Serial.print("L QRD TRIPPED");
      pivotRight();
      break;
    case 2:
    Serial.print("R QRD TRIPPED");
      pivotLeft();
      break;
    case 3:
    Serial.print("BOTH QRD TRIPPED");
      reverse();
      break;
    default:
      forward();
      break;
  }
  
}

void setMotor(int speed, boolean leftDir, boolean rightDir){
   analogWrite(enablePinL, speed);
   digitalWrite(in1PinL, leftDir);
   digitalWrite(in2PinL, !leftDir);
   analogWrite(enablePinR, speed);
   digitalWrite(in1PinR, rightDir);
   digitalWrite(in2PinR, !rightDir);
}


int isQrdTripped(){
  int q0, q1;
  QrdValue0 = analogRead(QrdPin0); // LEFT
  QrdValue1 = analogRead(QrdPin1); // RIGHT

  if (QrdValue0 < QrdThreshold) { 
    q0 = 1;
  } else { 
    q0 = 0;
  }

  if (QrdValue1 < QrdThreshold) { 
    q1 = 2;
  } else { 
    q1 = 0;
  }
  return  q0 + q1;
  // 1 = L
  // 2 = R
  // 3 = BOTH
  // 0 = NONE
}
