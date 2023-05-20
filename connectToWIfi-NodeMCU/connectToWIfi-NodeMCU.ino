#include <ESP8266WiFi.h>

void connectToWifi(void);

void setup() {
  Serial.begin(115200);
  connectToWifi();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void connectToWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin("seedsphere", "YssabelJane25*");
  Serial.print("Connecting to Wifi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(200);
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Mac Address: ");
  Serial.println(WiFi.macAddress());
}
