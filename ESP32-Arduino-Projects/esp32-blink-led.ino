/*
This Arduino ESP32 project blinks the onboard LED, 
providing a simple introduction to C programming for microcontrollers. 
The code toggles the LED state with corresponding messages displayed on the serial monitor.
*/

const int onBoardLedPin = 2;

void setup() {
  pinMode(onBoardLedPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Hello World - ESP32 - LED - BLINK");
}

void loop() {
  digitalWrite(onBoardLedPin, HIGH);
  Serial.println("LED is ON");
  delay(1000);

  digitalWrite(onBoardLedPin, LOW);
  Serial.println("LED is OFF");
  delay(1000);
}
