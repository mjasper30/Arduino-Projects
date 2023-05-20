// tinkercad: working
// arduino: working

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const byte trigger_pin = 2;
const byte echo_pin = 3;
const byte button = 4;
const int tmpPin = A0;
float tmpReading, voltage, celcius, farenheit, percent;
int time, distance; 

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode (trigger_pin, OUTPUT); 
  pinMode (echo_pin, INPUT);
  pinMode (button, INPUT);
  pinMode(tmpPin, INPUT);
}

void loop(){ 
  int buttonStatus = digitalRead(button);
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_pin, LOW);
  time = pulseIn (echo_pin, HIGH);
  distance = (time * 0.034) / 2;
  
  tmpReading = analogRead(tmpPin);
  percent = tmpReading / 1023.0;
  voltage = percent * 5.0;
  celcius = voltage * 100.0;
  
  if (buttonStatus == HIGH) {
    lcd.clear();
    lcd.print(distance);
    lcd.print("cm");
  }else{
    lcd.clear();
    lcd.print(celcius);
    lcd.print("C");
  }
  delay(1000);
}
