// tinkercad: working
// arduino: not yet tried

const int gas_input = A0;
int gas = 0;
const int led = 6;
const int buzzer = 12;

void setup(){
  pinMode(led,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  gas  = analogRead(gas_input);
  Serial.println(gas);
  int led_out = map(gas, 80, 400, 0, 255); //remapping the value of input from mq2 to 0-255
  tone(buzzer,led_out,100);
  analogWrite(led,led_out);
  delay(100);
}
