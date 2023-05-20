// tinkercad: not working
// arduino: not working

const byte led = 13;
const byte sensorPin = 12;
int sensor = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  sensor = digitalRead(sensorPin);
  
  if(sensor == HIGH){
    Serial.println("Motion detected!");
    digitalWrite(led, HIGH);
    delay(2000);
    
    Serial.println("Motion Ended!");
    digitalWrite(led, LOW);
  }
}
