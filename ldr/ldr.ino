//set pin numbers
//const won't change
const int ledPin = 13;
const int ldrPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); //initialize the LED pin as an output
  pinMode(ldrPin, INPUT); //initialize the LDR pin as an input
}

void loop() {
  int ldrStatus = analogRead(ldrPin);

  //check if the LDR status is <=300
  //if it is, the LED is HIGH
  if(ldrStatus <= 300){
    digitalWrite(ledPin, HIGH);
    Serial.println("LDR detect dark, turn the led ON");
  }
  else{
    digitalWrite(ledPin, LOW);
    Serial.println("LDR detect light, turn the led OFF");
  }
}
