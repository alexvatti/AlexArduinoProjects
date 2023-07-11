#define t1  20
#define t2  100
#define t3  50

void setup() {
  // set up pins 2 to 13 as outputs
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  effect_1();
  effect_1();
  effect_2();
  effect_2();
  effect_3();
  effect_3();
  effect_4();
  effect_4();
}

void effect_1() //50
{
  for(int i = 2; i < 14; i++) {
    digitalWrite(i, HIGH);
    delay(t3);
  }
  
  for(int i = 2; i < 14; i++) {
    digitalWrite(i, LOW);
    delay(t3);
  }
  
  for(int i = 13; i >= 2; i--) {
    digitalWrite(i, HIGH);
    delay(t3);
  }
  
  for(int i = 13; i >= 2; i--) {
    digitalWrite(i, LOW);
    delay(t3);
  }
}

void effect_2() //100
{
  for(int j = 2; j <= 13; j++) {
    digitalWrite(j, HIGH);
    delay(t2);
    j = j + 1;
  }
  
  for(int j = 2; j <= 13; j++) {
    digitalWrite(j, LOW);
    delay(t2);
  }
  
  for(int k = 13; k >= 2; k--) {
    digitalWrite(k, HIGH);
    delay(t2);
    k = k - 1;
  }
  
  for(int k = 13; k >=2; k--) {
    digitalWrite(k, LOW);
    delay(t2);
  }
}

// Left to right and right to left
void effect_3() { //20
  for(int i = 2; i < 13; i++) {
    digitalWrite(i, HIGH);
    delay(t1);
    digitalWrite(i + 1, HIGH);
    delay(t1);
    digitalWrite(i + 2, HIGH);
    delay(t1);
    digitalWrite(i, LOW);
    delay(t1);
    digitalWrite(i + 1, LOW);
    delay(t1);
  }
  
  for(int i = 13; i > 1; i--) {
    digitalWrite(i, HIGH);
    delay(t1);
    digitalWrite(i - 1, HIGH);
    delay(t1);
    digitalWrite(i - 2, HIGH);
    delay(t1);
    digitalWrite(i, LOW);
    delay(t1);
    digitalWrite(i - 1, LOW);
    delay(t1);
  }
}

void effect_4() {
  int count = 13; // keeps track of second LED movement
  
  // Move first LED from left to right and second from right to left
  for (int i = 2; i < 13; i++) {
    clear();
    digitalWrite(i, HIGH);      // chaser 1
    digitalWrite(count, HIGH);  // chaser 2
    count--;
    
    // Stop LEDs from appearing to stand still in the middle
    if (count != 7) {
      delay(t2);
    }
  }
  
  // Move first LED from right to left and second LED from left to right
  for (int i = 13; i > 2; i--) {
    clear();
    digitalWrite(i, HIGH);      // chaser 1
    digitalWrite(count, HIGH);  // chaser 2
    count++;
    
    // Stop LEDs from appearing to stand still in the middle
    if (count != 8) {
      delay(t2);
    }
  }
}
void clear(void)
{
  for (int i = 2; i <= 13; i++) {
    digitalWrite(i, LOW);
  }
}
