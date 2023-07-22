//16x2 LCD INTERFACE WITH ARDUINO UNO BOARD
// It is connected Over I2C Interface
// SDA -  A4
// SCL -  A5
// VCC -  5V
// GND -  ARDUINO UNO GND

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#define sensorPin A0
#define BUZZER 8
void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("ARDUINO PROJECTS");
  lcd.setCursor(0,1);
  lcd.print("RAIN DETECTOR SENSOR");
  pinMode(BUZZER,OUTPUT);
}

void loop()
{
  int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
  Serial.print("Analog output: ");
  Serial.println(sensorValue);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RAIN FALL STATUS:");
  lcd.setCursor(0,1);
  if (sensorValue > 700) {
    lcd.print("NO RAIN");
  } else if (sensorValue > 500) {
    lcd.print("LOW-MEDIUM RAIN");
  } else if (sensorValue > 300) {
    lcd.print("MEDIUM RAIN");
  } else  {
    lcd.print("HEAVY RAIN");
    digitalWrite(BUZZER,HIGH);
  }
  delay(1000);
  digitalWrite(BUZZER,LOW);
}
