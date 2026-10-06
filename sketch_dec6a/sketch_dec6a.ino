#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
const int servoPin = 6;
const int potPin = A1;
const int trigPin = 9, echoPin = 10;
double timing = 0.0;
double distance = 0.0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;
void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.print("Hello");
  pinMode(potPin, INPUT);
  myServo.attach(servoPin);
  myServo.write(0);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delay(2);

  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  timing = pulseIn(echoPin, HIGH);
  distance = (timing * 0.034) / 2;
  int potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 0, 180);
  lcd.print(potValue);
  myServo.write(potValue);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm\n");
  lcd.clear();

  distance = map(distance, 0, )
    delay(30);
}
