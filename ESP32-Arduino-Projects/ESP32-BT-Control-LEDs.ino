#include <BluetoothSerial.h>
BluetoothSerial SerialBT;
const int LED1 = 2;
const int LED2 = 4;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // Bluetooth device name
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW); // Initially turn off LED1
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW); // Initially turn off LED2
}

void loop() {
  if (SerialBT.available()) {
    String data = SerialBT.readString();
    handleData(data);
  }
}
void handleData(String data) {
  Serial.println(data);
  if (data == "led1 on") {
    digitalWrite(LED1, HIGH); // Turn on LED1
    SerialBT.println("LED1 turned on");
    Serial.println("LED1 turned on");
  } else if (data == "led1 off") {
    digitalWrite(LED1, LOW); // Turn off LED1
    SerialBT.println("LED1 turned off");
    Serial.println("LED1 turned off");
  }  else if (data == "led2 on") {
    digitalWrite(LED2, HIGH); // Turn on LED2
    SerialBT.println("LED2 turned on");
    Serial.println("LED2 turned on");
  }else if (data == "led2 off") {
    digitalWrite(LED2, LOW); // Turn off LED2
    SerialBT.println("LED2 turned off");
    Serial.println("LED2 turned off");
  }
}
