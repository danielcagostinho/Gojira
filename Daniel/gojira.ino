// motor vars
const unsigned int enablePinL = 11; 
const unsigned int enablePinR = 3;
const unsigned int in1PinL = 10;
const unsigned int in2PinL = 9;
const unsigned int in1PinR = 4;
const unsigned int in2PinR = 2;
const unsigned int maxSpeed = 255;
unsigned int speed;
unsigned int starting_speed = 0.6*maxSpeed;

// QRD
const unsigned int QrdThreshold = 700;
const unsigned int QrdPin0 = A0;
const unsigned int QrdPin1 = A1;
unsigned int QrdValue0;
unsigned int QrdValue1;
boolean white;

boolean enemySpotted;
boolean forwardL = true;
boolean forwardR = true;

enum State {
  SEARCHING,
  WAITING};

State currentState;

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

speed = starting_speed;

// Test code
  Serial.begin(9600);
  Serial.println("+-------------------------------------------+");
  Serial.println("|            QRD Sensor Readings            |");
  Serial.println("+-------------------------------------------+");

currentState = WAITING;
delay(5000);
}

void loop() {
  switch (currentState){
    case WAITING:
      currentState = SEARCHING;
      break;
    case SEARCHING:
      
      while(isQrdTripped() == 0){// check if this method updates or stays at initial value
        pivotLeft();
        ultrasense();
        if (enemySpotted = true){
          
        }
    case: QRD_TRIPPED
  }


}

void ultrasense(){


  
}

void bufferMotor(){
   analogWrite(enablePinL, 0);
   digitalWrite(in1PinL, 1;
   digitalWrite(in2PinL, 0);
   analogWrite(enablePinR, 0);
   digitalWrite(in1PinR, 1);
   digitalWrite(in2PinR, 0);
   delay(10);
}

void pivotLeft(){
  speed = 0.8*maxSpeed;
  forwardL = false;
  forwardR = true;
  setMotor(speed, forwardL, forwardR);
}

void pivotRight(){
  speed = 0.8*maxSpeed;
  forwardL = true;
  forwardR = false;
  setMotor(speed, forwardL, forwardR);
}

void reverse(){
  speed = maxSpeed;
  forwardL = false;
  forwardR = false;
  setMotor(speed, forwardL, forwardR);
}

void moveAwayFromBoundary(int qrdNum){ // 1 for left 0 for right
  switch(qrdNum){
    case 1:
      pivotRight();
      break;
    case 2:
      pivotLeft();
      break;
    case 3:
      reverse();
      break;
    default:
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
  QrdValue0 = analogRead(QrdPin0);
  QrdValue1 = analogRead(QrdPin1);

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
}

