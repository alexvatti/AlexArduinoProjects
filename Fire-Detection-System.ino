#define  RED_LED 13
#define  FIRE_ANALOG A2
#define  BUZZER 11
#define  THRESHOLD 100
int fire_analog_value=0;

void setup() {

  pinMode(RED_LED,OUTPUT);
  pinMode(FIRE_ANALOG,INPUT);
  pinMode(BUZZER,OUTPUT);
}
void loop() {
  fire_analog_value=analogRead(FIRE_ANALOG); 
  if (fire_analog_value<=THRESHOLD) { 
    digitalWrite(RED_LED,HIGH); 
    tone(BUZZER,100);
    delay(1000); 
  }
  else{
    digitalWrite(RED_LED,LOW); 
    noTone(BUZZER);
  }
}
