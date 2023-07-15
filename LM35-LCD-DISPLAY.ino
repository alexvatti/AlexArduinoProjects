//16x2 LCD INTERFACE WITH ARDUINO UNO BOARD
// It is connected Over I2C Interface
// SDA -  A4
// SCL -  A5
// VCC -  5V
// GND -  ARDUINO UNO GND

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("ARDUINO PROJECTS");
  lcd.setCursor(0,1);
  lcd.print("TEMP:");
}

void loop()
{
  int temp_digital=analogRead(A0);
  float temp_value = temp_digital * 0.10742187; 
  //10mv - Represnt - 1 degree Celecious
  //500/1024 = Will get Zeo 
  //500/1024 = 0.48828125 - 5V REF
  //110/1024 = 0.107421875 -1.1V REF
  //0.48828125; // (500/1024); //0.107421875;
  lcd.setCursor(0,0);
  lcd.print("ARDUINO PROJECTS");
  lcd.setCursor(0,1);
  lcd.print("TEMP:");
  lcd.print(temp_value);
  lcd.print(" ");
  lcd.print((char)223);
  lcd.print("C     ");
  delay(1000);
}
