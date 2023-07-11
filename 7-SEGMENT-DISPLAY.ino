//7 SEGMENT DISPLAY - COMMON ANODE CODE
//2 TO 8 PINS OF ARDUINO -CONNECTED TO A TO G OF 7 SEGMENT DISPLAY

//setup -set the pins as output direction
void setup() {
  for (int i=2;i<=9;i++)
    pinMode(i,OUTPUT);
}

//this function take the value in hex , then extract the bit by bit
// based on the bit value, it will drive the corresponding Arduino PIN 
//Low or  High
void drive_leds(int val)
{
  int digit_pin=2;
  int bit;
  for(int i=0;i<=6;i++)
  {
    bit = val & (1 << i);
    if(bit)
      digitalWrite(digit_pin,HIGH);
    else 
      digitalWrite(digit_pin,LOW);
    digit_pin++;
  }
}
// the loop routine runs over and over again forever:
void loop() {
  drive_leds(0x40);  //Displaying 0
  delay(1000);
  drive_leds(0x79);  //Displaying 1
  delay(1000);
  drive_leds(0x24);  //Displaying 2
  delay(1000);
  drive_leds(0x30);  //Displaying 3
  delay(1000);
  drive_leds(0x19);  //Displaying 4
  delay(1000);
  drive_leds(0x12);  //Displaying 5
  delay(1000);
  drive_leds(0x02);  //Displaying 6
  delay(1000);
  drive_leds(0x78);  //Displaying 7
  delay(1000);
  drive_leds(0x00);  //Displaying 8
  delay(1000);
  drive_leds(0x10);  //Displaying 9
  delay(1000);
}
