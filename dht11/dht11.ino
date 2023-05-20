// tinkercad: not yet tried
// arduino: working

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN  A0
#define DHTTYPE DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  delay(delayMS);
  sensors_event_t event;
  // Get temperature event and print its value.
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.print(F("Error reading temperature! "));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.print(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F(" Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
