// tinkercad: working
// arduino: not yet tried

const int tempPin = A0;
float reading, voltage, celcius, percent;

void setup(){
  Serial.begin(9600);
  pinMode(tempPin, INPUT);
}

void loop(){
  reading = analogRead(tempPin);
  percent = reading / 1023.0;
  voltage = percent * 5.0;
  celcius = voltage * 100.0;
  Serial.println(celcius);
  delay(1000);
}
