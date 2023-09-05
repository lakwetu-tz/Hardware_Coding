#include <SoftwareSerial.h>
SoftwareSerial sim800(10, 11);
#include <ArduinoJson.h>

 float volts;
  int amphere;
  int watts;
  float temperature;
  int humidity;
  int pressure;
  float smoke;
  int load;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sim800.begin(9600);
  Serial.println("Initializing ...");

}

void ShowSerialData()
{
  while (sim800.available() != 0)
    Serial.write(sim800.read());
  delay(1000);
 
}

void loop() {
  // put your main code here, to run repeatedly:

  if (sim800.available())
  Serial.write(sim800.read());
 
  sim800.println("AT");
  delay(3000);
 
  sim800.println("AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  delay(6000);
  ShowSerialData();
 
  sim800.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");//APN
  delay(6000);
  ShowSerialData();
 
  sim800.println("AT+SAPBR=1,1");
  delay(6000);
  ShowSerialData();
 
  sim800.println("AT+SAPBR=2,1");
  delay(6000);
  ShowSerialData();
 
 
  sim800.println("AT+HTTPINIT");
  delay(6000);
  ShowSerialData();
 
  sim800.println("AT+HTTPPARA=\"CID\",1");
  delay(6000);
  ShowSerialData();
 
  StaticJsonDocument<200> doc; 
  
  doc["volt"] = volts;
  doc["current"] = amphere;
  doc["energy"] = watts;
  doc["humidity"] = humidity;
  doc["temperature"] = temperature;
  doc["pressure"] = pressure;
  doc["load"] = load;
  doc["smoke"] = smoke;

  String sendtoserver;
  serializeJson(doc, sendtoserver);
  Serial.println(" ");  
  serializeJsonPretty(doc, sendtoserver);
  delay(4000);
 
  sim800.println("AT+HTTPPARA=\"URL\",\"http://192.xxxxxxxxxxxxxxxxxxxxxxxx.com\""); //Server address
  delay(4000);
  ShowSerialData();
 
  sim800.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  delay(4000);
  ShowSerialData();
 
 
  sim800.println("AT+HTTPDATA=" + String(sendtoserver.length()) + ",100");
  Serial.println(sendtoserver);
  delay(6000);
  ShowSerialData();
 
  sim800.println(sendtoserver);
  delay(6000);
  ShowSerialData();
 
  sim800.println("AT+HTTPACTION=1");
  delay(6000);
  ShowSerialData();
 
  sim800.println("AT+HTTPREAD");
  delay(6000);
  ShowSerialData();
 
  sim800.println("AT+HTTPTERM");
  delay(10000);
  ShowSerialData;
}


