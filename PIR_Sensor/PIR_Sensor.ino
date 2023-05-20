int PIR = 3;
int PIR_value = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIR, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  PIR_value = analogRead(PIR);

  Serial.println(PIR_value);
  delay(1500);
}
