#include <Ultrasonic.h>

#include <Ultrasonic.h>


const unsigned int TxPin = 12;
const unsigned int RxPin = 13;

Ultrasonic leftSonar(TxPin, RxPin);

void setup() {
  pinMode(TxPin, OUTPUT);
  pinMode(RxPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  printUltrasonicDistance();
  delay(1000);
}

void printUltrasonicDistance() {
  int distance = leftSonar.Ranging(CM);
  
  if (distance < 5) {
    Serial.println("Distance is less than 5cm");
  } else if (distance < 10){
    Serial.println("Distance is between 5cm and 10cm");
  } else if (distance < 15){
    Serial.println("Distance is between 10cm and 15cm");
  } else {
    Serial.println("Distance is too far to care about");
  }
}

