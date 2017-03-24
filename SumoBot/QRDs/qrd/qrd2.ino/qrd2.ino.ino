const unsigned int QrdPin0 = A0;
const unsigned int QrdPin1 = A1;
const unsigned int QrdThreshold1 = 800;
const unsigned int QrdThreshold2 = 750; // must change, probs dynamically in a setup routine

unsigned int QrdValue0;
unsigned int QrdValue1;

void setup() {
  pinMode(QrdPin0, INPUT);
  pinMode(QrdPin1, INPUT);

  Serial.begin(9600);
  Serial.println("+-------------------------------------------+");
  Serial.println("|            QRD Sensor Readings            |");
  Serial.println("+-------------------------------------------+");
}

void loop() {
  QrdValue0 = analogRead(QrdPin0);
  QrdValue1 = analogRead(QrdPin1);
  Serial.println("Qrd 0");
  Serial.println(QrdValue0);
  if (QrdValue0 < QrdThreshold1) {
      Serial.println("Qrd0 is reading white!!!");
    } else {
      Serial.print("Qrd0 is reading black!!!");
    }
    
  Serial.println("Qrd 1");
  Serial.println(QrdValue1);
  if (QrdValue1 < QrdThreshold1) {
      Serial.println("Qrd1 is reading white!!!");
    } else {
      Serial.print("Qrd1 is reading black!!!");
    }
  Serial.print("\n");
  Serial.println("---------------------------------------------");

  delay(1000);
}



