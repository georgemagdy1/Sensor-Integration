#include <DHT.h>

#define DHTPIN 3
#define MOTION_PIN 2
#define pinLed 4
#define pinBuzzer 5
#define DHT_type DHT22

DHT dht(DHTPIN, DHT_type);

void setup() {
  Serial.begin(9600);
  pinMode(MOTION_PIN, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  static bool lightFlag = false; // Declare lightFlag as a static variable

  // Read motion sensor
  int motionState = digitalRead(MOTION_PIN);

  // Adjust tasks based on sensor readings
  if (motionState == HIGH) {
    // Toggle the lightFlag and adjust LEDs accordingly
    lightFlag = !lightFlag;
    digitalWrite(pinLed, lightFlag ? HIGH : LOW);
    digitalWrite(pinBuzzer, lightFlag ? HIGH : LOW);
  } else {
    digitalWrite(pinLed, LOW);
    digitalWrite(pinBuzzer, LOW);
    lightFlag = false;
  }
  delay(500);

  // Read temperature and humidity from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Add temperature-based tasks here, e.g., adjust thermostat

  // Print sensor readings to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Delay for a short time to avoid rapid readings
  delay(500);
}

