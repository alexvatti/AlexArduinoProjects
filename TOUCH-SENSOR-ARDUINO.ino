#define TOUCH_INPUT 10
#define RED_LED 12

void setup() {
  // put your setup code here, to run once:
  pinMode(TOUCH_INPUT,INPUT);
  pinMode(RED_LED,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(TOUCH_INPUT)){
    digitalWrite(RED_LED,HIGH);
    delay(10);
  }else {
  digitalWrite(RED_LED,LOW);
  }
  delay(50); //delay
}
