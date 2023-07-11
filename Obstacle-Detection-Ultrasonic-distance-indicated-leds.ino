//Obstacle Detection with Ultrasonic Sensors 
//Display the Distance on LEDS (RED, YELLOW, GREEN)

#include <NewPing.h>
const int TriggerPin = 11;
const int EchoPin = 12;

#define RED_LED 2
#define YELLOW_LED 3
#define GREEN_LED 4

// 100 = maxDistance
NewPing sonar(TriggerPin, EchoPin, 100);

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED,OUTPUT);
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);
}

void loop() {
 
  int distance = sonar.ping_cm();
  Serial.println(distance);

  if (distance <=5) {
    digitalWrite(RED_LED,HIGH);
    digitalWrite(YELLOW_LED,LOW);
    digitalWrite(GREEN_LED,LOW);
  } else if (distance <=10) {
    digitalWrite(RED_LED,LOW);
    digitalWrite(YELLOW_LED,HIGH);
    digitalWrite(GREEN_LED,LOW);
  } else {
    digitalWrite(RED_LED,LOW);
    digitalWrite(YELLOW_LED,LOW);
    digitalWrite(GREEN_LED,HIGH);
  }
  delay(100); //50 to100 ms
}
