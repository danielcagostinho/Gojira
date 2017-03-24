// init the const (pins)
int enablePinL = 11; 
int enablePinR = 3;
int in1PinL = 10;
int in2PinL = 9;
int in1PinR = 4;
int in2PinR = 2;

enum D_State {FORWARD, STILL, REVERSE, PIVOTL, PIVOTR};
const unsigned int maxSpeed = 255;
unsigned int speed = 1*maxSpeed;
D_State currentState = FORWARD;
boolean reverseL = false;
boolean reverseR = false;


void setup() {
pinMode(in1PinL, OUTPUT); 
pinMode(in2PinL, OUTPUT); 
pinMode(in1PinR, OUTPUT); 
pinMode(in2PinR, OUTPUT); 
pinMode(enablePinL, OUTPUT); 
pinMode(enablePinR, OUTPUT); 
}

void loop() {
changeState();
setMotor(speed, reverseL, reverseR);
delay(3000);
}



void changeState() {
  if (currentState == FORWARD) {
    currentState = STILL;
    speed = 0*maxSpeed;
  } else if (currentState == STILL) {
    currentState = REVERSE;
    speed = 1*maxSpeed;
    reverseL = true;
    reverseR = true;
  } else if (currentState == REVERSE) {
    currentState = PIVOTL;
    speed = 1*maxSpeed;
    reverseL = true;
    reverseR = false;
  } else if (currentState == PIVOTL) {
    currentState = PIVOTR;
    speed = 1*maxSpeed;
    reverseL = false;
    reverseR = true;
  } else if (currentState == PIVOTR) {
    currentState = FORWARD;
    speed = 1*maxSpeed;
    reverseL = false;
    reverseR = false;
  }
  
}

void setMotor(int speed, boolean reverseL, boolean reverseR) {
analogWrite(enablePinL, speed); 
analogWrite(enablePinR, speed);
digitalWrite(in1PinL,!reverseL); 
digitalWrite(in2PinL,reverseL);
digitalWrite(in1PinR,reverseR); 
digitalWrite(in2PinR,!reverseR);
}

