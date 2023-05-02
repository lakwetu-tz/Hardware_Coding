
HardwareSerial mySerial(2);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    mySerial.begin(9600, SERIAL_8N1, 15, 2);

     Serial.println("sending...");
      mySerial.write("H");
   
}

void loop() {
 
}