// Define the joystick analog input pins
const int xAxisPin = A0;
const int yAxisPin = A1;

int i, X_Neutral = 0, Y_Neutral = 0;

int B; // Blue LED brightness
int R; // Red LED brightness
int Y; // Yellow LED brightness
int G; // Green LED brightness

// Define the pins for the LEDs
const int B_PIN = 11; // Blue LED pin
const int R_PIN = 10; // Red LED pin
const int Y_PIN = 9;  // Yellow LED pin
const int G_PIN = 6;  // Green LED pin

void setup() {
  // Initialize serial communication at a baud rate of 9600
  Serial.begin(9600);
  
  // Calculate the neutral joystick values by averaging multiple readings
  for (i = 1; i <= 10; i++) {
    X_Neutral += analogRead(xAxisPin);
    Y_Neutral += analogRead(yAxisPin);
  }
  X_Neutral = X_Neutral / 10;
  Y_Neutral = Y_Neutral / 10;
}

void loop() {
  // Read the analog values from the joystick
  int xAxisValue = analogRead(xAxisPin);
  int yAxisValue = analogRead(yAxisPin);

  // Print the joystick values to the serial monitor
  Serial.print("X-Axis: ");
  Serial.print(xAxisValue);
  Serial.print("\tY-Axis: ");
  Serial.println(yAxisValue);

  // Control the Red and Blue LEDs based on X-axis joystick movement
  if (xAxisValue >= X_Neutral) {
    B = 0;
    R = map(xAxisValue, X_Neutral, 1023, 0, 255);
  } else {
    R = 0;
    B = map(xAxisValue, X_Neutral, 0, 0, 255);
  }

  // Control the Green and Yellow LEDs based on Y-axis joystick movement
  if (yAxisValue >= Y_Neutral) {
    Y = 0;
    G = map(yAxisValue, Y_Neutral, 1023, 0, 255);
  } else {
    G = 0;
    Y = map(yAxisValue, Y_Neutral, 0, 0, 255);
  }

  // Set the LED brightness using analogWrite
  analogWrite(R_PIN, R);
  analogWrite(B_PIN, B);
  analogWrite(Y_PIN, Y);
  analogWrite(G_PIN, G);

  // Add a delay to control the serial output rate
  delay(100);
}
