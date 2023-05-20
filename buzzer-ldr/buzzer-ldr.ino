// tinkercad: working
// arduino: working

const byte buzzer = 2;
const byte ldr = A0;
int ldrReading = 0;

void setup(){
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT);
  Serial.begin(9600);
}

void loop(){
  ldrReading = analogRead(ldr);
  tone(buzzer, ldrReading, 1000);
  
  if(ldrReading < 200){
    noTone(buzzer);
  }
  Serial.println(ldrReading);
}
