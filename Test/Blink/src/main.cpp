#include <Arduino.h>

// put function declarations here:
// int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  pinMode(D4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D4, HIGH);
  delay(500);
   digitalWrite(D4, LOW);
  delay(500);
}

// put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }