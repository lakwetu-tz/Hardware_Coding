#include <HTTPClient.h>
#include <WiFi.h>

const char* ssid = "*******";
const char* password = "******";

void setup(){
	Serial.begin(115200);

	Serial.println("Connecting to WiFi");

  	WiFi.begin(ssid, password);

  	while (WiFi.status() != WL_CONNECTED) {
  		delay(1000);
  		Serial.println("Connecting to WiFi...");
 	}

  // Serial.println("Connected to WiFi");
}

void loop(){
	if (WiFi.status == WL_CONNECTED){
		HTTPClient http;

    		http.begin("https://**********************.heroku.com/api/v1/amount/");

     		
    		http.addHeader("Content-Type", "application/x-www-form-urlencoded");


	    	String requestBody = "uid=" + tagID + "&amount=" + amount_entered;

	    	int httpResponseCode = http.POST(requestBody);

	    	if (httpResponseCode > 0) {
	      		String response = http.getString();
	      		Serial.println("Response: " + response);

	      		if (strstr(response.c_str(), "SUCCESSFUL TRANSACTION") != NULL) {
				Serial.println("Success");
	      		} else {
				Serial.println("No success");
      			}


    		} else {
      			Serial.print("Error sending request: ");
      			Serial.println(httpResponseCode);
    	}


    	http.end();
	
    delay(5000);  // Send the request every 5 seconds
  }
