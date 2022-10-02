#include <WiFi.h>
#include "ThingSpeak.h"


const char* ssid = "MySsid";
const char* password = "MyPassword";
const int ldrPin = 35;

WiFiClient wifiClient;
unsigned long myChannelNumber = 1;
const char* myWriteApiKey = "MyWriteApiKey";

void setup() {
  Serial.begin(9600);
  pinMode(ldrPin, INPUT);

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(wifiClient);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED){
    Serial.print("\nAttempting to connect...");

    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, password);
      delay(5000);
    }
    Serial.print("\nConnected");
  }

  int ldrStatus = analogRead(ldrPin);

  int response = ThingSpeak.writeField(myChannelNumber, 1, ldrStatus, myWriteApiKey);

  if (response == 200){
    Serial.print("\nChannel Update Successful");
  }
  else{
    Serial.println("Couldn't Update Channel. Http Code: " + response);
  }

}
