// activity 1
// tinkercad: working
// arduino: working

int arr[] = {2,3,4,5,6,7,8,9,10};
int i, j;

void setup() {
  for(i=0; i<11; i++){
    pinMode(arr[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  for(i=0; i<11; i++){
    if(i == 8){
      for(j=0; j<3; j++){
        digitalWrite(arr[i], HIGH);
        delay(1000);
        digitalWrite(arr[i], LOW);
        delay(1000);
      }

      digitalWrite(arr[i], HIGH);
      delay(2000);
      digitalWrite(arr[i], LOW);
      delay(2000);
      digitalWrite(arr[i], HIGH);
      delay(2000);
      digitalWrite(arr[i], LOW);
      delay(2000);
      digitalWrite(arr[i], HIGH);
      delay(2000);
      digitalWrite(arr[i], LOW);
      delay(500);

      for(j=0; j<3; j++){
        digitalWrite(arr[i], HIGH);
        delay(1000);
        digitalWrite(arr[i], LOW);
        delay(1000);
      }
      delay(5000);
      return;
    }
    digitalWrite(arr[i], HIGH);
    delay(1000);
    digitalWrite(arr[i], LOW);
  }
}
