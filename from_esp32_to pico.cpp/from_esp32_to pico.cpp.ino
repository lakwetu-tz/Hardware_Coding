
UART mySerial(0, 1, NC, NC);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.print("Leg's go");

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  while (mySerial.available() > 0) {
    char received_signal = mySerial.read();
    Serial.println("receiving...");
    Serial.println(received_signal);

    if (received_signal == 'H') {
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
    }
  }
}