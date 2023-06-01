// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
//#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
//#define BLYNK_TEMPLATE_NAME         "Device"
//#define BLYNK_AUTH_TOKEN            "YourAuthToken"

#define BLYNK_TEMPLATE_ID "TMPL6iJn0iMil"
#define BLYNK_TEMPLATE_NAME "SmartWaterTan"
#define BLYNK_AUTH_TOKEN "IKDattlGNHRgDgnMbM-mRJIJzeQV6X8u"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <NewPing.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Lab";
char pass[] = "12345678";



#define TRIGGER_PIN D0    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN D1       // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.

BlynkTimer timer;
void sendSensor() {
  delay(50);  // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());  // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  Blynk.virtualWrite(V0, sonar.ping_cm());
}

// #define Pompa D4
int SW_State = 0;

BLYNK_WRITE(V1) {
  SW_State = param.asInt();
  if (SW_State == 1) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Pompa HIDUP");
    Blynk.virtualWrite(V1, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Pompa MATI");
    Blynk.virtualWrite(V1, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}