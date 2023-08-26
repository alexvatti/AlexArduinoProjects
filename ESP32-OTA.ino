#include <WiFi.h>        // For connecting ESP32 to WiFi
#include <ArduinoOTA.h>  // For enabling over-the-air updates

// Replace with your network credentials
const char* ssid     = "TP-Link_375D";
const char* password = "11862574";

void setup() {

  WiFi.begin(ssid, password);  // Connect to WiFi - defaults to WiFi Station mode

  // Ensure WiFi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  ArduinoOTA.begin();  // Starts OTA
  pinMode(2, OUTPUT); 
}

void loop() {

  ArduinoOTA.handle();  // Handles a code update request

  // All loop you're code goes here.
  digitalWrite(2, LOW);
  delay(1000);
  digitalWrite(2, HIGH);
  delay(1000);
}
