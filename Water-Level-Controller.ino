/*
Automatic water level controller switches ON the motor 
when the water level in the tank becomes low (desired prefixed lower limit)
making sure that water is present in the sump.
It switches OFF the motor once the tank becomes full
*/

#include <NewPing.h>
const int TriggerPin = 11;
const int EchoPin = 12;

// 100 = maxDistance
NewPing sonar(TriggerPin, EchoPin, 100);

void setup() {
  Serial.begin(9600);
  pinMode(3,OUTPUT);
}

void loop() {
 
  int distance = sonar.ping_cm();
  Serial.println(distance);
  if (distance > 0) {
    if (distance <=4 ) {
      Serial.println("Case 1: Below 4cm from Top/Tip of Tank ,Turn Off Motor");
      digitalWrite(3,LOW);
    } else if (distance <=10) {
      Serial.println("Case 2: Below 10cm from Top/Tip of Tank, Turn On Motor");
      digitalWrite(3,HIGH);
    } else if (distance <=15) {
      Serial.println("Case 3: Below 15cm from Top/Tip of Tank, Turn On Motor");
      digitalWrite(3,HIGH);
    } else {
      Serial.println("Case 4: Below 15cm from Top/Tip of Tank, Turn On Motor");
      digitalWrite(3,HIGH);
    }
  }
  delay(100); //50 to100 ms
}
