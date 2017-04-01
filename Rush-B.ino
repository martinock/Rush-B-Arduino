#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified module
int sensorPin = A0; // select the input pin for ldr
int sensorValue = 0; // variable to store the value coming from the sensor
unsigned long startTime = 0;
unsigned long elapsed = 0;

void setup()
{
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH); // NOTE: You can turn the backlight off by setting it to LOW instead of HIGH
    lcd.begin(16, 2);
    lcd.clear();
    pinMode(13, OUTPUT);
    elapsed = millis();
}

void loop()
{
    if (elapsed - startTime < 1000) {      
      sensorValue = analogRead(sensorPin); // read the value from the sensor
      lcd.setCursor(0,0);
      if (sensorValue < 200) {
        digitalWrite(13, HIGH);       
        lcd.print("Low Light");
      } else {
        digitalWrite(13, LOW);
        lcd.print("Press the button");
        lcd.setCursor(0,1);
        lcd.print("to get the code");
      }
      elapsed = millis();
    } else {
      lcd.clear();
      startTime = millis();
      elapsed = millis();
    }
}
