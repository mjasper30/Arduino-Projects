// tinkercad: working
// arduino: working

int led = 4, button = 5;
int mode = 0, old = 0, current;

void setup() {
  pinMode(led,OUTPUT);
  pinMode(button,INPUT);

  Serial.begin(9600);
}

void loop() {
  int current = digitalRead(button);
  if(current == 0 && old == 1){
    if(mode == 0){
      digitalWrite(led, HIGH);
      Serial.println("currently ON");
      mode = 1;
    }
    else{
      digitalWrite(led, LOW);
      Serial.println("currently ON=FF");
      mode = 0;
    }
    delay(500);
  }
  old = current;
}
