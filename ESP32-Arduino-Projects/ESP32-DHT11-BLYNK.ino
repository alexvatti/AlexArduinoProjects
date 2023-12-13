#define BLYNK_TEMPLATE_ID "TMPL2TqLrtTZY"
#define BLYNK_TEMPLATE_NAME "ESP32DHT"
#define BLYNK_AUTH_TOKEN "il2qgmGNyvElM7fxxBeeqWhxIJsrxV7G"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DFRobot_DHT11.h>

// Replace with your network credentials
const char* ssid     = "TP-Link_375D";
const char* password = "11862574";

DFRobot_DHT11 DHT;
#define DHT11_PIN 4

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

void sendSensor()
{
  DHT.read(DHT11_PIN);
  float t= DHT.temperature;
  float h= DHT.humidity;
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Serial.print("Temperature : ");
  Serial.println(t);
  Serial.print("Humidity : ");
  Serial.println(h);
}
void setup()
{   
  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
