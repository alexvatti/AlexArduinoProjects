
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <TM1637Display.h>

// Define the connections pins
#define CLK 5
#define DIO 6
TM1637Display display = TM1637Display(CLK, DIO);
static int flag=1;
void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC");
  Serial.println("-------------------");
  // Set the display brightness (0-7)
	display.setBrightness(5);
	// Clear the display
	display.clear();
}

void loop() {
  tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    if (flag==1) {
      display.showNumberDecEx(tm.Hour,0b01000000,false,2,0);
      flag=!flag;
    } else {
      display.showNumberDec(tm.Hour, false, 2, 0); 
      flag=!flag;
    }
    print2digits(tm.Minute);
    display.showNumberDec(tm.Minute, false, 2, 2); 
    Serial.write(':');
    print2digits(tm.Second);
    Serial.println();

  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(500);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
