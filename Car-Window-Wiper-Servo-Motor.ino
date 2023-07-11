//Car Window Wiper Using Servo Motor

#include <NewPing.h>
#include <Wire.h> 
#include<Servo.h>

#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

Servo myservo;

NewPing ultrasonic_sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup()
{
  Serial.begin(9600);   // Open serial monitor
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  myservo.attach(9);
  delay(2000);
}

void loop()
{
  int distance = ultrasonic_sensor.ping_cm();

  if (distance > 0){
    int angel = map(distance,1,30,10,180);
    myservo.write(angel);
    
 }
delay(50);
}
