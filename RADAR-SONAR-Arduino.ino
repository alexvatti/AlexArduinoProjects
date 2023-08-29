// Includes the Servo library
#include <Servo.h>
#include <NewPing.h>

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int TriggerPin = 11;
const int EchoPin = 12;
// 100 = maxDistance
NewPing sonar(TriggerPin, EchoPin, 100);

// Variables for the duration and the distance
long duration;
int distance;

Servo myServo; // Creates a servo object for controlling the servo motor
void setup() {
  Serial.begin(9600);
  myServo.attach(9); // Defines on which pin is the servo motor attached
}
void loop() {

   // rotates the servo motor from 5 to 175 degrees
  for(int i=5;i<=175;i++){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
  Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 175 to 5 degrees
  for(int i=175;i>5;i--){  
  myServo.write(i);
  delay(30);
  distance = calculateDistance();
  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
  
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  return sonar.ping_cm();
}
