// tinkercad: working
// arduino: working

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int seconds;
const int tmpPin = A0;
float tmpReading, voltage, celcius, farenheit, percent;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  lcd.begin(0,0);
  lcd.backlight();
  pinMode(tmpPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  lcd.setCursor(0, 1);
  lcd.print(seconds);
  tmpReading = analogRead(tmpPin);
  percent = tmpReading / 1023.0;
  voltage = percent * 5.0;
  celcius = voltage * 100.0;
  
  Serial.println(celcius);
  delay(500);
  
  lcd.begin(16, 2);
  lcd.print(celcius); 
}
