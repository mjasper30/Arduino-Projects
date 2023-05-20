#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 5

int led = 13;                // the pin that the LED is atteched to
int sensor = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

//gas
int LED = A1;
const int gas = 0;
int MQ2pin = A0;

#define DHTTYPE DHT11
//#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  dht.begin(); // initialize dht
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
}

void loop(){
  //PIR
//  val = digitalRead(sensor);   // read sensor value
//  if (val == HIGH) {           // check if the sensor is HIGH
//    digitalWrite(led, HIGH);   // turn LED ON
//    delay(100);                // delay 100 milliseconds 
//    
//    if (state == LOW) {
//      Serial.println("Motion detected!"); 
//      lcd.clear();
//      lcd.setCursor(0,0);
//      lcd.print("Motion detected!");
//      state = HIGH;       // update variable state to HIGH
//      delay(5000);
//    }
//  } 
//  else {
//      digitalWrite(led, LOW); // turn LED OFF
//      delay(200);             // delay 200 milliseconds 
//      
//      if (state == HIGH){
//        Serial.println("Motion stopped!");
//        lcd.clear();
//        lcd.setCursor(0,0);
//        lcd.print("Motion stopped!");
//        state = LOW;       // update variable state to LOW
//        delay(5000);    }
//  }

  //TEMPERATURE AND HUMIDITY
  float h = dht.readHumidity();
  // Read temperature as Celcius (the default)
  float f = dht.readTemperature();
  
  // Read temperature as Fahrenheit (isFahrenheiht = true) 
  float t = dht.readTemperature(true);

  // Check if any reads failed and exit early
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.print("Failed to read from DHT sensor!");
  }
  
  lcd.setCursor(0,0);
  lcd.print(t);
  lcd.print((char)223);
  lcd.print("F|");
  lcd.print(f);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" F\t");
  Serial.print("Temperature: ");
  Serial.print(f);
  Serial.print(" C\t");
  Serial.println();

//  //GAS
//  float sensorValue,MQ2pin;
//  sensorValue = analogRead(MQ2pin); // read analog input pin 0
//
//  if(sensorValue >= 50){
//    digitalWrite(LED,HIGH);
//    Serial.print("Sensor Value: ");
//    Serial.println(sensorValue);
//    Serial.println(" |SMOKE DETECTED");
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("SMK: " + (String)sensorValue);
//    lcd.setCursor(0,1);
//    lcd.print("SMOKE DETECTED");
//  }
//  else{
//    digitalWrite(LED,LOW);
//    Serial.print("Sensor Value: ");
//    Serial.println(sensorValue);
//    Serial.println(" |NO SMOKE DETECTED");
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("SMK: " + (String)sensorValue);
//    lcd.setCursor(0,1);
//    lcd.print("NO SMOKE DETECTED");
//  } 
//  delay(500);

//END OF LOOP
}

float getsensorValue(int pin){
    return (analogRead(pin));
}
