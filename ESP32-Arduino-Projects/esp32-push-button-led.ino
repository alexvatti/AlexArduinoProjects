/*
This Arduino ESP32 project, reads a push button's state on pin 4 and toggles an LED on pin 2 accordingly,
showcasing basic input and output control. 
The program illuminates the LED for one second when the button is pressed and turns it off otherwise.
*/

const int LedPin = 2;
const int buttonPin = 4;

void setup() {
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.println("Hello World");
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(LedPin, HIGH);
    Serial.println("Input is High - Hence LED is ON");
    delay(1000);
  } else {
    digitalWrite(LedPin, LOW);
    Serial.println("Input is Low - Hence LED is LOW");
    delay(1000);
  }
}
