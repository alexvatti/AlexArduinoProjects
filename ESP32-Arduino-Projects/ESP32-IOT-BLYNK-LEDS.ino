#define BLYNK_TEMPLATE_ID "TMPL2N5JbrAmS"
#define BLYNK_TEMPLATE_NAME "LEDCONTROL"
#define BLYNK_AUTH_TOKEN "irPmLO7UToZLkHy7HrvVjwl9BNRMsGzP"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Replace with your network credentials
const char* ssid     = "TP-Link_375D";
const char* password = "11862574";
char auth[] = BLYNK_AUTH_TOKEN;
int RED_LED = 2;
int BLUE_LED = 4;        

void setup() {  
  pinMode(RED_LED, OUTPUT); 
  pinMode(BLUE_LED, OUTPUT); 
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  Blynk.begin(auth,ssid,password);
} 
  

void loop(){
   Blynk.run();
}

// Function to control LEDs based on virtual pin values
BLYNK_WRITE(V0) {
  int Value = param.asInt();
  digitalWrite(RED_LED, Value);
}

// Function to control LEDs based on virtual pin values
BLYNK_WRITE(V1) {
  int Value = param.asInt();
  digitalWrite(BLUE_LED, Value);
}
