#include <TM1637Display.h>

#define OUTPUT_A 3    // Define pin 3 as OUTPUT_A
#define OUTPUT_B 4    // Define pin 4 as OUTPUT_B

// Define the connections pins
#define CLK 5
#define DIO 6
TM1637Display display = TM1637Display(CLK, DIO);

int OUTPUT_A_STATE;   // Store the state of OUTPUT_A
int counter = 0;      // Initialize a counter variable

void setup() {   
  pinMode (OUTPUT_A,INPUT);
  pinMode (OUTPUT_B,INPUT);
  display.setBrightness(5);
  // Clear the display
  display.clear();
  Serial.begin(9600); // Initialize serial communication
  OUTPUT_A_STATE = digitalRead(OUTPUT_A); // Read and store the initial state of OUTPUT_A
  display.showNumberDec(counter);
}

void loop() {
  int CURRENT_OUTPUT_A_STATE = digitalRead(OUTPUT_A); // Read the current state of OUTPUT_A

  // Check if the current state of OUTPUT_A is different from the stored state
  if (CURRENT_OUTPUT_A_STATE != OUTPUT_A_STATE) {
    // Check if OUTPUT_B is in the same state as OUTPUT_A
    if (digitalRead(OUTPUT_B) != CURRENT_OUTPUT_A_STATE) {
      counter++; // If OUTPUT_B is different, increment the counter
    } else {
      if (counter > 0 )
        counter--; // If OUTPUT_B is the same, decrement the counter
    }
    display.showNumberDec(counter);
    Serial.println(counter); // Print the current value of the counter
  }
  
  OUTPUT_A_STATE = CURRENT_OUTPUT_A_STATE; // Update the stored state of OUTPUT_A
}
