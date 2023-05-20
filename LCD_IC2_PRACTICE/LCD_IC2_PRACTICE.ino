//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Jasper Macaraeg");
  lcd.setCursor(0,1);
  lcd.print("BSCS");
}


void loop()
{
  lcd.scrollDisplayLeft();
  delay(1000);
//  lcd.setCursor(0,0);
//  lcd.print("Jasper Macaraeg");
//  delay(3000);
//  lcd.clear();
//  delay(1000);
}
