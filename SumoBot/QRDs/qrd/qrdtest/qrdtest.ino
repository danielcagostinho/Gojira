const unsigned int QrdPin = A0; // The pin that the Qrd sensor is connected to
const unsigned int QrdThreshold = 950; // Threshold for deciding if Qrd is reading white/black.
                                     // This value will need to be calibrated (10 is not going to work!)
float voltage;
unsigned int QrdValue; // Global variable where the reading can be stored

// setup() will only run once. This is where you will set up your pins, Serial monitor, or anything else
// (**hint** like your 5s delay) in here.
void setup() {
  pinMode(QrdPin, INPUT);

  Serial.begin(9600); // Starts serial monitoring on port 9600
                      // Note: The serial ports on Arduino boards use pins 0 & 1 (RX & TX) for serial
                      //       communication, make sure that you DON'T use these pins for your robot

  // Use print() and println() like in java to print to Serial port
  Serial.println("+-------------------------------------------+");
  Serial.println("|            QRD Sensor Readings            |");
  Serial.println("+-------------------------------------------+");
}


// loop() is arduino's "main()" method, but is really just a while(true) {} loop. This will repeat as 
// fast as possible and never stop until the arduino is reset. When setup() is finished loop() will
// be called automatically. This is where your logic will go.
void loop() {
  QrdValue = analogRead(QrdPin); // Read the current value of the analog pin. Will return a 10-bit number
                                 // Hint: This is a good way to calibrate the threshold!

  //Serial.println("Qrd is reading a value of : " + QrdValue);
  voltage = QrdValue;
  // print out the value you read:
   Serial.println(QrdValue);

  Serial.println(voltage);
  if (QrdValue < QrdThreshold) {
      Serial.println("Qrd is reading white!!!");
    } else {
      Serial.print("Qrd is reading black!!!");
      Serial.print("\n");
    }
  Serial.println("---------------------------------------------");

  delay(100); // Wait one second before next loop iteration starts
               // Note: the delay() function is BLOCKING meaning that no code will run until the delay
               //      time has completely finished.
}



