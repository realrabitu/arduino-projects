#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int ledSafe = 10, ledDanger= 11, sensorPin = A1;
void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(sensorPin, INPUT);
  pinMode(ledSafe, OUTPUT);
  pinMode(ledDanger, OUTPUT);
  }

void loop() {
  int sensorState = analogRead(sensorPin);
  if (sensorState != HIGH){
    lcd.setCursor(0, 0);
    lcd.print("No Earthquake");
    lcd.setCursor(0, 1);
    lcd.print("Detected");
    digitalWrite(ledDanger, LOW);
    digitalWrite(ledSafe, HIGH);
  }
  else {
    lcd.setCursor(0, 0);
    lcd.print("Earthquake");
    lcd.setCursor(0, 1);
    lcd.print("Detected!");
    digitalWrite(ledSafe, LOW);
    digitalWrite(ledDanger, HIGH);
  }
  delay(50);
}