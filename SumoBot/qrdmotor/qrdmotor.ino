// motor vars
const unsigned int enablePinL = 11; 
const unsigned int in1PinL = 10;
const unsigned int in2PinL = 9;
const unsigned int maxSpeed = 255;
unsigned int speed;

// QRD
const unsigned int QrdThreshold = 1000;
const unsigned int QrdPin = A0;
unsigned int QrdValue;
boolean white;
float voltage;

void setup() {
// motor
pinMode(in1PinL, OUTPUT); 
pinMode(in2PinL, OUTPUT); 
pinMode(enablePinL, OUTPUT);

// QRD
 pinMode(QrdPin, INPUT);

// Test code
  Serial.begin(9600);
  Serial.println("+-------------------------------------------+");
  Serial.println("|            QRD Sensor Readings            |");
  Serial.println("+-------------------------------------------+");
  speed = 255;
}

void loop() {
  QrdValue = analogRead(QrdPin);
  if (QrdValue < QrdThreshold) {
    Serial.println("White");
    analogWrite(enablePinL, 0*speed);
    digitalWrite(in1PinL, 1);
    digitalWrite(in2PinL, 0);
  } else {
    Serial.println("Black");
    Serial.println("\n");
    analogWrite(enablePinL, speed);
    digitalWrite(in1PinL, 1);
    digitalWrite(in2PinL, 0);
  }
   Serial.println("---------------------------------------------");
   delay(10);
}
