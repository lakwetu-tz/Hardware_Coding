#include <SoftwareSerial.h>
SoftwareSerial sim800(12, 13);

struct{
  float volts;
  int amphere;
  int watts;
  float temp;
  int humid;
  int pressure;
  float smoke;
  int load;
} values;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  sim800.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}

String GenerateJsonData(){
  String aux = "{\n\t\"volt\":\"";
  aux.concat(String(values.volts));
  aux.concat("\",\n\t\"current\":\"");
  aux.concat(String(values.amphere));
  aux.concat("\",\n\t\"energy\":");
  aux.concat(String(values.watts));
  aux.concat("\",\n\t\"temp\":");
  aux.concat(String(values.temp));
  aux.concat("\",\n\t\"pressure\":");
  aux.concat(String(values.pressure));
  aux.concat("\",\n\t\"humidity\":");
  aux.concat(String(values.humid));
  aux.concat("\",\n\t\"load\":");
  aux.concat(String(values.load));
  aux.concat("\",\n\t\"smoke\":");
  aux.concat(String(values.smoke));
  
  aux.concat("\n}");
  return aux;
}

void TumaSasaBaba(){
  String jsonData = GenerateJsonData();
  String apn = "";
  
  sim800.println("AT");
  delay(100);
  sim800.println("AT+CREG?");
  delay(500);
   sim800.println("AT+SAPBR=3,1,Contype,GPRS");
  delay(800);
  sim800.println("AT+SAPBR=3,1,APN," + apn);
  delay(800);
  sim800.println("AT+SAPBR =1,1");
  delay(800);
  sim800.println("AT+SAPBR=2,1");
  delay(800);
  sim800.println("AT+HTTPINIT");
  delay(800);
  sim800.println("AT+HTTPPARA=?");
  sim800.println("AT+HTTPPARA=CID,1");
  delay(800);
  sim800.println("AT+HTTPPARA=URL, http://endpoint.com/api/mainboard/values");
  delay(2000);
  sim800.println("AT+HTTPPARA=CONTENT, application/json");
  sim800.print("AT+HTTPDATA=");
  sim800.println(jsonData.length() + 2); // Add 2 for extra bytes
  delay(100);
  sim800.println(jsonData);
  delay(100);
  sim800.println("AT+HTTPACTION=1"); // Send HTTP POST request
  delay(5000);                 
  
  while(sim800.available() != 0){
    Serial.write(sim800.read());
  }
}

