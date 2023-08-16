/*
 * Arduino with PIR motion sensor
 * GND , PIR OUTPUT, VCC
 */
 
int RED_LED = 11;                // choose the pin for the RED LED
int PIR_INPUT = 7;               // choose the input pin (for PIR SENOSR)
int PIR_STATE = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(RED_LED, OUTPUT);      // declare LED as output
  pinMode(PIR_INPUT, INPUT);     // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
  val = digitalRead(PIR_INPUT);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(RED_LED, HIGH);  // turn LED ON
    if (PIR_STATE == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      PIR_STATE = HIGH;
    }
  } else {
    digitalWrite(RED_LED, LOW); // turn LED OFF
    if (PIR_STATE == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      PIR_STATE = LOW;
    }
  }
}
