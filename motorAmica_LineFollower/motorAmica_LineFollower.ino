
#include <ESP8266WiFi.h>
#define senKi  D7
#define senKa D8

int PWMA = 5;  //Right side
int PWMB = 4;  //Left side
int DA = 0;    //Right reverse
int DB = 2;    //Left reverse

int sensor_kiri = 0;
int sensor_kanan = 0;



void setup() {

  // Debug console
  Serial.begin(9600);

  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DA, OUTPUT);
  pinMode(DB, OUTPUT);

  pinMode(senKi, INPUT);

  pinMode(senKa, INPUT);
}



void loop() {
  // Blynk.run();

  sensor_kiri = digitalRead(senKi);
  sensor_kanan = digitalRead(senKa);

  if (sensor_kiri == 0 && sensor_kanan == 0) {
    Serial.println("Maju");
  } else {
    if (sensor_kiri == 1 && sensor_kanan == 0) {
      Serial.println("Kanan");
    } else {
      if (sensor_kiri == 0 && sensor_kanan == 1) {
        Serial.println("Kiri");
      } else {
        if (sensor_kiri == 1 && sensor_kanan == 1) {
          Serial.println("Stop");
        } else {
        }
      }
    }
  }

  // motorF();
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