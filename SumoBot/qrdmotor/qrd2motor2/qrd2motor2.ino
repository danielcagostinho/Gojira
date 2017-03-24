// motor vars
const unsigned int enablePinL = 11; 
const unsigned int enablePinR = 3;
const unsigned int in1PinL = 10;
const unsigned int in2PinL = 9;
const unsigned int in1PinR = 4;
const unsigned int in2PinR = 2;
const unsigned int maxSpeed = 255;
unsigned int speed;

// QRD
const unsigned int QrdThreshold = 950;
const unsigned int QrdPin0 = A0;
const unsigned int QrdPin1 = A1;
unsigned int QrdValue0;
unsigned int QrdValue1;
boolean white;

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

// Test code
  Serial.begin(9600);
  Serial.println("+-------------------------------------------+");
  Serial.println("|            QRD Sensor Readings            |");
  Serial.println("+-------------------------------------------+");
  speed = 255;
}

void loop() {
  QrdValue0 = analogRead(QrdPin0);
  QrdValue1 = analogRead(QrdPin1);
  
  if ((QrdValue0 < QrdThreshold) || (QrdValue1 < QrdThreshold)) {
    Serial.println("White");
    analogWrite(enablePinL, 0*speed);
    digitalWrite(in1PinL, 1);
    digitalWrite(in2PinL, 0);
    analogWrite(enablePinR, 0*speed);
    digitalWrite(in1PinR, 1);
    digitalWrite(in2PinR, 0);
  } else {
    Serial.println("Black");
    Serial.println("\n");
    analogWrite(enablePinL, speed);
    digitalWrite(in1PinL, 1);
    digitalWrite(in2PinL, 0);
    analogWrite(enablePinR, speed);
    digitalWrite(in1PinR, 1);
    digitalWrite(in2PinR, 0);
  }
   Serial.println("---------------------------------------------");
   delay(10);
}
