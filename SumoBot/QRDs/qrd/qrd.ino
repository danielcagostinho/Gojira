const unsigned int qrdPin1 = A0;
const unsigned int qrdPin2 = A1;
const unsigned int qrdPin3 = A2;
const unsigned int qrdPin4 = A3;
const unsigned int qrdThreshold = 10;

unsigned int qrdValue1;
unsigned int qrdValue2;
unsigned int qrdValue3;
unsigned int qrdValue4;

boolean qrd1State = 0;
boolean qrd2State = 0;
boolean qrd3State = 0;
boolean qrd4State = 0;

const unsigned int refRate = 1000;

void setup() {
  pinMode(qrdPin1, INPUT);
  pinMode(qrdPin2, INPUT);
  pinMode(qrdPin3, INPUT);
  pinMode(qrdPin4, INPUT);

  Serial.begin(9600); // Starts serial monitoring on port 9600
                      // Note: The serial ports on Arduino boards use pins 0 & 1 (RX & TX) for serial
                      //       communication, make sure that you DON'T use these pins for your robot

  // Use print() and println() like in java to print to Serial port
  Serial.println("+-------------------------------------------+");
  Serial.println("|            QRD Sensor Readings            |");
  Serial.println("+-------------------------------------------+");
}

void loop(){
  qrd1State = qrd1Read();
  qrd2State = qrd2Read();
  qrd3State = qrd3Read();
  qrd4State = qrd4Read();
  delay(refRate);
}

boolean qrd1Read(){
   qrdValue1 = analogRead(qrdPin1);
  if (qrdValue1 < qrdThreshold) {
    return 1;
  } else {
    return 0;
  }
}

boolean qrd2Read(){
   qrdValue2 = analogRead(qrdPin2);
  if (qrdValue2 < qrdThreshold) {
    return 1;
  } else {
    return 0;
  }
}
boolean qrd3Read(){
   qrdValue3 = analogRead(qrdPin3);
  if (qrdValue3 < qrdThreshold) {
    return 1;
  } else {
    return 0;
  }
}
boolean qrd4Read(){
   qrdValue4 = analogRead(qrdPin4);
  if (qrdValue4 < qrdThreshold) {
    return 1;
  } else {
    return 0;
  }
}

