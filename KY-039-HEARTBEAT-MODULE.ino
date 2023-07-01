/*
KY-039 HEART BEAT SENSOR MODULE
1. READING THE A/D SIGNAL
2. TAKING AVG OF 10 SAMPLES
3. SENDING THE DATA TO UART TO LAPTOP
4. DELAY OF 10 milli Seconds
5. Reapeat the Process
*/

#define HEARTBEAT_ANALOG A0
void setup() {
  //A0 -A/D -Input
  pinMode(HEARTBEAT_ANALOG, INPUT);
  //UART -9600-8N1 -Initialization
  Serial.begin(9600);
}

void loop() {
  float pulse;
  int pulse_sum = 0;
  //tsking 10 samples
  for (int i = 0; i < 10; i++)
    pulse_sum += analogRead(HEARTBEAT_ANALOG);
  //avg of 10 samples
  pulse = pulse_sum / 10.00;
  //print on UART
  Serial.println(pulse);
  delay(10); //10 milli seconds
}
