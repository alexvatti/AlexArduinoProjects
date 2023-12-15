//16x2 LCD INTERFACE WITH ESP32 BOARD
// It is connected Over I2C Interface
// SDA -  SDA
// SCL -  SCL
// VCC -  5V
// GND -  ESP32 GND

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the I2C address of the LCD module
const int lcdAddress = 0x27;

// Set the LCD dimensions (16 columns and 2 rows)
const int lcdColumns = 16;
const int lcdRows = 2;

// Create an LCD object
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);

void setup() {
  // Initialize the LCD
  lcd.init();
  
  // Turn on the backlight
  lcd.backlight();

  // Set the cursor to the first position on the first line
  lcd.setCursor(0, 0);

  // Print a message to the LCD
  lcd.print("ESP32 PROJECTS");

  // Set the cursor to the first position on the second line
  lcd.setCursor(0, 1);

  // Print another message to the LCD
  lcd.print("PLS SUBSCRIBE");
}

void loop() {
  // Your main code can go here
  // For simplicity, the example only initializes the LCD once and displays a static message
    // Set the cursor to the first position on the first line
  lcd.setCursor(0, 0);

  // Print a message to the LCD
  lcd.print("ESP32 PROJECTS");

    // Set the cursor to the first position on the second line
  lcd.setCursor(0, 1);

  // Print another message to the LCD
  lcd.print("ALEX ARDUINO");

  delay(1000);

  lcd.clear();
  delay(1000);
}
