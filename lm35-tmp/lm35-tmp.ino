// tinkercad: working
// arduino: working

const int tmpPin = A0;
float tmpReading, voltage, celcius, farenheit, percent;

void setup() {
  Serial.begin(9600);
  pinMode(tmpPin, INPUT);
}

void loop() {
  tmpReading = analogRead(tmpPin);
  percent = tmpReading / 1023.0;
  voltage = percent * 5.0;
  celcius = voltage * 100.0;

  Serial.println(celcius);
  delay(1000);
}
