int sensorPin = 2;
volatile long pulse;
unsigned long lastTime;
int  volume;
void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
}
void loop() {
  volume = 2.663 * pulse;
  int volume2=map(volume,0,1000,0,1000);
  Serial.print("Ammount of volume");
  Serial.print(volume2);
  delay(300); 
  
}
void increase() {
  pulse++;
}
