int enablePinL = 11; 
int in1PinL = 10;
int in2PinL = 9;
int enablePinR = 3;
int in1PinR = 4;
int in2PinR = 2;


enum D_State {FORWARD, STILL, REVERSE, PIVOTL, PIVOTR};
const unsigned int maxSpeed = 255;
unsigned int speed = 1*maxSpeed;
D_State currentState = FORWARD;
boolean reverseL = false;

void setup() {
  // put your setup code here, to run once:
pinMode(in1PinL, OUTPUT); 
pinMode(in2PinL, OUTPUT); 
pinMode(enablePinL, OUTPUT);
pinMode(in1PinR, OUTPUT); 
pinMode(in2PinR, OUTPUT); 
pinMode(enablePinR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//changeState();
setMotor(speed, reverseL);
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
  } else if (currentState == REVERSE) {
    currentState = PIVOTL;
    speed = 1*maxSpeed;
    reverseL = true;
  } else if (currentState == PIVOTL) {
    currentState = PIVOTR;
    speed = 1*maxSpeed;
    reverseL = false;
  } else if (currentState == PIVOTR) {
    currentState = FORWARD;
    speed = 1*maxSpeed;
    reverseL = false;
  }
  
}

void setMotor(int speed, boolean reverseL) {
analogWrite(enablePinL, speed); 
digitalWrite(in1PinL,!reverseL); 
digitalWrite(in2PinL,reverseL);
analogWrite(enablePinR, speed); 
digitalWrite(in1PinR,reverseL); 
digitalWrite(in2PinR,!reverseL);
}

