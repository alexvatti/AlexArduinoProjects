// Define constants for the soil moisture sensor, water pump relay, and threshold
#define SOIL_SENSOR A0
#define WATER_PUMP_RELAY 8
#define THRESHOLD 350

void setup() {
  // Initialize the serial communication for debugging
  Serial.begin(9600);

  // Set the water pump relay pin as an output
  pinMode(WATER_PUMP_RELAY, OUTPUT);

  // Turn off the water pump relay (initially)
  digitalWrite(WATER_PUMP_RELAY, LOW);

  // Wait for 1 second for initialization
  delay(1000);
}

void loop() {
  // Read the analog value from the soil moisture sensor
  int value = analogRead(SOIL_SENSOR);

  // Check if the soil moisture value is very low (<= 25)
  if (value <= 25) {
    // If soil moisture is extremely low, turn off the water pump
    digitalWrite(WATER_PUMP_RELAY, LOW);
  } else {
    // Check if soil moisture is below the defined threshold
    if (value < THRESHOLD) {
      // If soil moisture is below the threshold, keep the water pump off
      digitalWrite(WATER_PUMP_RELAY, LOW);
    } else {
      // If soil moisture is above the threshold, turn on the water pump
      digitalWrite(WATER_PUMP_RELAY, HIGH);
    }

    // Add a small delay to prevent rapid switching of the pump
    delay(100);
  }

  // Print the soil moisture value to the serial monitor for debugging
  Serial.println(value);
}
