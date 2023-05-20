// tinkercad: not yet tried
// arduino: working

int moistureValue;
float moisture_percentage;

void setup() {
  Serial.begin(9600);
}

void loop() {
  moistureValue = analogRead(A0);
  moisture_percentage = ((moistureValue/539.00)*100);
  Serial.print("\n Moisture Value: ");
  Serial.print(moisture_percentage);
  Serial.print("%");
  delay(1000);
}
