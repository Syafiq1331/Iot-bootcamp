
#include <ESP8266WiFi.h>

int PWMA = 5;  //Right side
int PWMB = 4;  //Left side
int DA = 0;    //Right reverse
int DB = 2;    //Left reverse

int jarak = 0;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup() {

  // Debug console
  Serial.begin(9600);

  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DA, OUTPUT);
  pinMode(DB, OUTPUT);
}



void loop() {
  // Blynk.run();

  jarak = 0.01723 * readUltrasonicDistance(D7, D8);
  Serial.print("Jarak ");
  Serial.println(jarak);
  if (jarak >= 100 && jarak <= 300) {
    motorB();
  } else {
    motorF();
  }
}


void motorBL() {
  //BackWard and Left
  digitalWrite(PWMA, LOW);
  digitalWrite(DA, LOW);

  digitalWrite(PWMB, HIGH);
  digitalWrite(DB, HIGH);
}
void motorLT() {
  //Left Turn
  digitalWrite(PWMA, 450);
  digitalWrite(DA, HIGH);

  digitalWrite(PWMB, 450);
  digitalWrite(DB, LOW);
}
void motorFL() {
  //Forward and Left
  digitalWrite(PWMA, LOW);
  digitalWrite(DA, LOW);

  digitalWrite(PWMB, HIGH);
  digitalWrite(DB, LOW);
}
void motorB() {
  //BackWard
  digitalWrite(PWMA, HIGH);
  digitalWrite(DA, HIGH);

  digitalWrite(PWMB, HIGH);
  digitalWrite(DB, HIGH);
}
void motorS() {
  //Stay
  digitalWrite(PWMA, LOW);
  digitalWrite(DA, LOW);

  digitalWrite(PWMB, LOW);
  digitalWrite(DB, LOW);
}
void motorF() {
  //Forward
  digitalWrite(PWMA, HIGH);
  digitalWrite(DA, LOW);

  digitalWrite(PWMB, HIGH);
  digitalWrite(DB, LOW);
}

void motorBR() {
  //Backward and Right
  digitalWrite(PWMA, HIGH);
  digitalWrite(DA, HIGH);

  digitalWrite(PWMB, LOW);
  digitalWrite(DB, LOW);
}
void motorRT() {
  //Right turn
  digitalWrite(PWMA, 450);
  digitalWrite(DA, LOW);

  digitalWrite(PWMB, 450);
  digitalWrite(DB, HIGH);
}

void motorFR() {
  //Forward and Right
  digitalWrite(PWMA, HIGH);
  digitalWrite(DA, LOW);

  digitalWrite(PWMB, LOW);
  digitalWrite(DB, LOW);
}