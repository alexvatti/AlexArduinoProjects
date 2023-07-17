#include <IRremote.h>
int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define RED_LED 2
#define YELLOW_LED 3
#define GREEN_LED 4
static int RED_LED_STATE = 1;
static int YELLOW_LED_STATE = 1;
static int GREEN_LED_STATE = 1;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(RED_LED,OUTPUT);
  pinMode(YELLOW_LED,OUTPUT);
  pinMode(GREEN_LED,OUTPUT);

}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    //dump(&results);
    irrecv.resume(); // Receive the next value

    if(results.value==0x40BF7A85)                                       
    {
        Serial.println("1 PRESSED");
        digitalWrite(RED_LED, RED_LED_STATE);
        RED_LED_STATE = !RED_LED_STATE;

    } else  if(results.value==0x40BFBA45)                                       
    {
        Serial.println("2 PRESSED");
        digitalWrite(YELLOW_LED, YELLOW_LED_STATE);
        YELLOW_LED_STATE = !YELLOW_LED_STATE;
    }else if(results.value==0x40BF7887)                                       
    {
        Serial.println("3 PRESSED");
        digitalWrite(GREEN_LED, GREEN_LED_STATE);
        GREEN_LED_STATE = !GREEN_LED_STATE;
    }else {

    }
    
    delay(10);
  }
}
