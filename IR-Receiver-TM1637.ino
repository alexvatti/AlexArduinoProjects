//https://www.facebook.com/photo/?fbid=24585343807719635&set=gm.1969868563394544&idorvanity=876213069426771
/*
  I'm working on a project using both the TM1637 display and the IR remote sensor. 
  I find that, although a project that uses one or the other will work fine, using both doesn't appear to work. 
  The IR sensor works the first time you press a button on the remote, the display will show the button code, but then everything locks up.
  If I comment out the one line that displays the button code, everything is fine.
  Anyone have a clue for me? This is a simple sketch to demonstrate the problem:
*/


#include <TM1637Display.h>
#include <Wire.h>
#include <IRremote.h>

// Define the connection pins
#define CLK 5
#define DIO 4
#define RECV_PIN 3

// Create an instance of the TM1637Display class
TM1637Display display = TM1637Display(CLK, DIO);

// Create an instance of the IRrecv class and decode_results struct
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  irrecv.enableIRIn(); // Start the IR receiver
  Serial.begin(9600);
  
  while (!Serial) ; // Wait for the serial connection to be established
  delay(200);
  Serial.println("IR WITH TM1637");
  
  // Set the display brightness (0-7)
  display.setBrightness(5);
  
  // Clear the display
  display.clear();
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value != 0xffffffff) { // Check for a valid IR code
      Serial.println(results.value, HEX); // Print the received IR code in hexadecimal
      display.showNumberHexEx(results.value); // Display the IR code on the TM1637 display
    }
    irrecv.resume(); // Receive the next IR code
  }
}
