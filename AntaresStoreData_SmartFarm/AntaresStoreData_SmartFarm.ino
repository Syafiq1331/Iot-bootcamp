/*
  This code will deploy data to your Antares project device with the following structure:
  (Note that nesting the JSON object can only be done up to 2 levels using this library)
  {
    "temperature": random-int,
    "humidity": random-int,
    "wind_speed": random-float,
    "rain_level": random-float,
    "location" : {
      "latitude": "static-string",
      "longitude": "static-string"
    }
  }
  For more information please visit https://antares.id/id/docs.html
*/

#include "AntaresESP8266HTTP.h"

#include <NewPing.h>
#include <DHT.h>
#include <MQUnifiedsensor.h>
#include <Servo.h>

#define ACCESSKEY "2d22910411917cf4:cb18431e8f415bbc"
#define WIFISSID "Robotic"
#define PASSWORD "idnmantab"

#define projectName "SmartFarm01"
#define deviceName "nodeSensor"

AntaresESP8266HTTP antares(ACCESSKEY);

//
#define TRIGGER_PIN D5    // Pin Trigger HC-SR04 pada NodeMCU
#define ECHO_PIN D6       //Pin Echo HC-SR04 pada NodeMCU
#define MAX_DISTANCE 250  //Maksimum Pembacaan Jarak (cm)
#define DHTPIN D4         //Define Pin DHT
#define DHTTYPE DHT11     //Define Jenis DHT
#define Pompa D0          //Define Pin Relay 1
#define Minum D1          //Define Pin Relay 2
#define LED2 D2           //Define Pin LED

char placa[] = "ESP8266";       //Define jenis board yang digunakan
#define Voltage_Resolution 5    //Tegangan yang digunakan
#define pin A0                  //Pin yang digunakan untuk MQ-135
#define type "MQ-135"           //Jenis MQ yang digunakan
#define ADC_Bit_Resolution 10   //Resolusi Bit ADC
#define RatioMQ135CleanAir 3.6  //Nilai Udara dianggap bersih


char LED[] = "led";
char RELAY1[] = "relay1";
char RELAY2[] = "relay2";
char SERVO[] = "servo";
char AMONIA[] = "amonia";
char KELEMBABAN[] = "kelembaban";
char SUHU[] = "suhu";
char KETINGGIAN[] = "ketinggian";
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);  //Aktifkan fungsi MQ
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);                               //Aktifkan Fungsi HCSR-04 //Aktifkan fungsi HC-SR04
DHT dht(DHTPIN, DHTTYPE);                                                         //Aktifkan Fungsi DHT
Servo servo;                                                                      //Aktifkan fungsi Servo

unsigned long durasiKirim = 0;
unsigned long jedaKirim = 2000;

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  /* Use wifiConnectionNonSecure instead if you don't want to use HTTPS
   * and avoid SNTP matching */
  //antares.wifiConnectionNonSecure(WIFISSID,PASSWORD);
  pinMode(LED2, OUTPUT);      //Set LED sebagai Output
  pinMode(Pompa, OUTPUT);     //Set Relay 1 sebagai Output
  pinMode(Minum, OUTPUT);     //Set Relay 2 sebagai Output
  digitalWrite(LED2, LOW);    //Set LED dengan Nilai LOW
  digitalWrite(Pompa, HIGH);  //Set Relay 1 dengan Nilai HIGH
  digitalWrite(Minum, HIGH);  //Set Relay 2 dengan Nilai HIGH

  dht.begin();                   //Memulai fungsi DHT
  servo.attach(13);              //Memulai fungsi Servo pada Pin 13
  MQ135.setRegressionMethod(1);  //_PPM = a*ratio^b //Set Method yang digunakan untuk MQ - 135
  MQ135.init();                  //Memulai fungsi MQ-135 //Fungsi untuk Kalibrasi MQ-135
  float calcR0 = 0;
  for (int i = 1; i <= 10; i++) {
    MQ135.update();
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0 / 10);
}

void loop() {
  // Variables
  // int temp = random(25, 30);
  // int hum = random(75, 90);
  // float windsp = float(random(20, 30)) / 3.33;
  // float rainlv = float(random(0, 20)) / 6.99;
  // String lat = "-6.8718189";
  // String lon = "107.5872477";

  // // Add variable data to storage buffer
  // antares.add("temperature", temp);
  // antares.add("humidity", hum);
  // antares.add("wind_speed", windsp);
  // antares.add("rain_level", rainlv);
  // antares.add("location", "latitude", lat);
  // antares.add("location", "longitude", lon);

  unsigned long time = millis();  //Fungsi Millis
  MQ135.update();                 //Update Nilai MQ-135
  MQ135.setA(102.2);
  MQ135.setB(-2.473);               //Set Nilai Sampling untuk NH4 / Amonia
  float NH4 = MQ135.readSensor();   //Hasil Pembacaan nilai Amonia
  int jarak = sonar.ping_cm();      //Hasil Pembacaan Jarak
  float h = dht.readHumidity();     //Hasil Pembacaan Humidity
  float t = dht.readTemperature();  //Hasil Pembacaan Suhu

  antares.add(KETINGGIAN, jarak);
  antares.add(SUHU, t);
  antares.add(KELEMBABAN, h);
  antares.add(AMONIA, NH4);
  // Send from buffer to Antares
  antares.send(projectName, deviceName);
  /*
    Uncomment the line below to use HTTP instead of HTTPS.
    Will be faster, but less secure
  */
  // antares.sendNonSecure(projectName, deviceName);
  delay(10000);
}
