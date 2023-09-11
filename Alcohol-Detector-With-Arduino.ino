/*MQ-3 sensor with Arduino.
  Included BUZZER and LED
  Cut off - 350 parts per million
  Adjusted the POT -such a way that D/O - LOW around 350 parts per million
*/

#define MQ3_DIGITAL 3
#define RED_LED 11
#define GREEN_LED 12
#define BUZZER 8
#define MQ3_ANALOG A1
 
void setup() {
  pinMode(MQ3_DIGITAL, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  bool mq3_digital = digitalRead(MQ3_DIGITAL);
  int mq3_analog = analogRead(MQ3_ANALOG);
 
  Serial.println("MQ-3 Analog value : ");
  Serial.println(mq3_analog);
  
  Serial.println("MQ-3 Digital value :");
  Serial.println(mq3_digital);
 
  if (mq3_analog >= 350 &&  mq3_digital == LOW ) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED,LOW);
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED,HIGH);
    digitalWrite(BUZZER, LOW);
  }
  delay(500);
}
