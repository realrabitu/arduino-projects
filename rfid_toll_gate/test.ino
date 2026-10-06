#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int redLED = 2, greenLED = 3, servoPin = 5, pushButton = 6;

Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  // initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  myServo.attach(servoPin);
  // set the servo to 0 degrees
  myServo.write(0);
}
void idleSequence(void) {
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
  myServo.write(0);
  lcd.print("Welcome to toll.");
  lcd.setCursor(0, 1);
  lcd.print("SCAN RFID CARD.");
}
void displayOpeningMessage(void) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Opening gate...");
}
void gateOpen(int speed = 20) {
  for (int angle = 0; angle <= 90; angle++) {
    myServo.write(angle);
    delay(speed);
  }
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
}

void displayProceedMessage(int maxCycles = 3, int arrowSpeed = 100) {
  lcd.clear();
  lcd.print("PLEASE PROCEED.");
  for (int cycle = 0; cycle < maxCycles; cycle++) {
    for (int col = 0; col < 16; col++) {
      lcd.setCursor(col, 1);
      lcd.print(">>>");
      delay(arrowSpeed);  // then prints the characters every 100 ms
      lcd.setCursor(col, 1);
      lcd.print("   ");  // overwrites previous arrows with spaces
    }
  }
}
void gateClose(int speed = 20) {
  for (int angle = 90; angle >= 0; angle--) {
    myServo.write(angle);
    delay(speed);
  }
}

void displayClosingMessage(void) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Closing...");
}

void unauthorizedSequence(void) {
  myServo.write(0);
  digitalWrite(ledPinRed, HIGH);
  digitalWrite(ledPinGreen, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You shall not");
  lcd.setCursor(3, 1);
  lcd.print("pass!");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UNAUTHORIZED CARD.");
  delay(3000);
}

void loop() {
  int buttonState = digitalRead(pushButton);
    if (buttonState == HIGH) {
      displayOpeningMessage();
      gateOpen(); // parameters: (speed) default: (20)
      displayProceedMessage(); // parameters: (maxCycle, arrowSpeed) default: (3, 100)
      displayClosingMessage(); 
      gateClose(); // parameters: (speed) default: (20)
    } else {
      idleSequence();
  }
}