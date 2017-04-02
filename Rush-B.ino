#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

const int buttonPin = 9;
const int ledPin = 11;
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified module
int sensorPin = A0; // select the input pin for ldr
int sensorValue = 0; // variable to store the value coming from the sensor
int buttonValue = HIGH;
boolean isScreenOff = false;
unsigned long startTime = 0;
const long debounceDelay = 500;
long lastDebounceTime = 0;
int brightness = 0;
int fadeAmount = 5;

void setup()
{
    //Setup LCD
    lcd.setBacklightPin(3,POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.begin(16, 2);
    lcd.clear();

    //Setup Pin
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT); 
}

void loop()
{
    //Handle Button Input
    buttonValue = digitalRead(buttonPin);

    //Handle LCD Delay per second
    if (millis() - startTime < 1000) {   
      sensorValue = analogRead(sensorPin); // read the value from the sensor
      lcd.setCursor(0,0);
      if (sensorValue < 200) {       
        lcd.print("Low Light");
        analogWrite(ledPin, brightness);
        brightness = brightness + fadeAmount;
        if (brightness <= 0 || brightness >= 255) {
          fadeAmount = -fadeAmount;
        }
        delay(20);
      } else {
        digitalWrite(ledPin, LOW);
        lcd.print("Press the button");
        lcd.setCursor(0,1);
        lcd.print("to get the code");
      }
    } else {
      lcd.clear();
      startTime = millis();
    }

    //Handle Button Delay
    if (millis() - lastDebounceTime > debounceDelay) {
      if (buttonValue == HIGH) {
        if (!isScreenOff) {
          lcd.setBacklight(LOW);
          isScreenOff = true;
          lastDebounceTime = millis();
        } else {
          lcd.setBacklight(HIGH);
          isScreenOff = false;
          lastDebounceTime = millis();
        }
      }
    }
}
