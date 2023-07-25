
#include <NewPing.h>
#include <Servo.h>

const int TriggerPin = 9;
const int EchoPin = 11;

// 100 = maxDistance
NewPing sonar(TriggerPin, EchoPin, 100);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 180;    // variable to store the servo position

void setup() {
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object
  myservo.write(180);
  Serial.begin(9600);
}
void open_gate()
{
    for (pos = 180; pos >= 90; pos -= 10) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
  }
}

void close_gate(){
  for (pos = 90; pos <= 180; pos += 10) { // goes from 0 degrees to 180 degrees
    // in steps of 2 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 15 ms for the servo to reach the position
  }
}

void toll_gate()
{
  open_gate();
  delay(3000);
  close_gate();
}
void loop() {
   int distance = sonar.ping_cm();
   if ((distance > 0) && (distance  <= 10)){
     Serial.println(distance);
     delay(100);
     int confirm_distance = sonar.ping_cm();
        if ((confirm_distance > 0) && (confirm_distance <= 10)){
            Serial.println(confirm_distance);
            toll_gate();
        }
   }
   delay(1000);
   myservo.write(180);

}
