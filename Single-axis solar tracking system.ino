/*
  Single-axis solar tracking system using Arduino
*/

// Include the servo motor library
#include <Servo.h>

// Define the LDR sensor pins
#define LDR1 A0
#define LDR2 A1

// Define the error value. You can change it as you like
#define error 20

// Starting point of the servo motor
int position = 90;

// Create an object for the servo motor
Servo servo;

void setup() {
  // Include servo motor PWM pin
  servo.attach(9);

  // Set the starting point of the servo
  servo.write(position);

  // Initialize serial communication for debugging
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // Get the LDR sensor value
  int ldr1 = analogRead(LDR1);

  // Get the LDR sensor value
  int ldr2 = analogRead(LDR2);

  // Get the difference of these values
  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);

  // Check these values using an IF condition
  if ((value1 <= error) || (value2 <= error)) {
    // If the difference in LDR values is within the defined error range, do nothing
  } else {
    // If the difference is outside the error range, adjust the servo position
    if (ldr1 > ldr2) {
      if (position < 180)
        position = ++position; // Increment the servo position if LDR1 is greater
    }
    if (ldr1 < ldr2) {
      if (position > 0)
        position = --position; // Decrement the servo position if LDR2 is greater
    }
  }

  // Write the new servo position
  servo.write(position);

  // Print sensor values and current servo position for debugging
  Serial.println("ldr1");
  Serial.println(ldr1);
  Serial.println("ldr2");
  Serial.println(ldr2);
  Serial.println(position);

  // Delay to control the rate of servo movement
  delay(100);
}
