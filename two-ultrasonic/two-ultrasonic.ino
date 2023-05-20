// tinkercad: not working
// arduino: not yet tried

//HC-SR04
const int trigPin = 13;
const int echoPin2 = 12;
float Hduration, Hdistance;

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop(){
  HCSensor();
  delay(1000);
}

void HCSensor(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Hduration = pulseIn(echoPin2, HIGH);
  Serial.print(Hdistance / 2) / 29.1;
  Serial.println(" in ");
  Serial.print(Hdistance);
  Serial.println(" cm ");
}
