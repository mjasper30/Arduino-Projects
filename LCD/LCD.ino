// C++ code
//
#include <LiquidCrystal_I2C.h>

int seconds = 0;

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
  lcd.begin(16, 2);
  lcd.init();
  lcd.setCursor(3, 0);
  //lcd.rightToLeft();
  lcd.print("hello, world!");
}

void loop()
{
  
}
