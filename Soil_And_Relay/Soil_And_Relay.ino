#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int sensorPin = A0;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int threshholdValue = 800;
bool relayValue = false;
const int relayPin = 3;
const int ledRed = 6;
const int ledGreen = 7;

void setup()
{ 
	// initialize the LCD
  Serial.begin(9600);
	lcd.begin();

 pinMode(relayPin, OUTPUT);
 pinMode(ledGreen, OUTPUT);
 pinMode(ledRed, OUTPUT);

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
}

void loop()
{
  int sensorValue = analogRead(sensorPin); // Read the sensor value
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MoistValue: "+(String) sensorValue );
  if(sensorValue < threshholdValue){
    Serial.println("Bulb On");
    digitalWrite(relayPin, HIGH);
    relayValue = true;
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }
  else{
    Serial.println("Bulb Off");
    digitalWrite(relayPin, LOW);
    relayValue = false;
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
  }
  lcd.setCursor(0, 1);
  lcd.print("RelayValue: "+ (String) relayValue);
  delay(1000);
}