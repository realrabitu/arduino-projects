#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int SS_PIN = 10, RST_PIN = 9, ledPinGreen = 7, ledPinRed = 8, servoPin = 6;

MFRC522 rfid(SS_PIN, RST_PIN);
Servo myServo;
String predefinedCardUID = "a575ad9b";  // enter the UID of the card to be read here
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();  // initialize the reader
  // initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  myServo.attach(servoPin);
  // set the servo to 0 degrees
  myServo.write(0);
}
/*
==============================================================================================
  FUNCTION: idleSequence - turns on red LED, turns off green LED, closes the servo gate, and
  displays a welcome message.
  PARAMETERS: none
==============================================================================================
*/
void idleSequence(void) {
  digitalWrite(ledPinRed, HIGH);
  digitalWrite(ledPinGreen, LOW);
  myServo.write(0);
  lcd.print("Welcome to toll.");
  lcd.setCursor(0, 1);
  lcd.print("SCAN RFID CARD.");
}
/*
============================================================================
  FUNCTION: displayOpeningMessage - displays a message while the gate opens.
  PARAMETERS: none
============================================================================
*/
void displayOpeningMessage(void) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Opening gate...");
}
/*
======================================================================================================
  FUNCTION: gateOpen - opens the servo gate, turns on green LED and turns off red LED.
  PARAMETERS: speed (default is 20) - sets the speed through the delay.
  Higher - slower
  Lower - faster
======================================================================================================
*/
void gateOpen(int speed = 20) {
  for (int angle = 0; angle <= 90; angle++) {
    myServo.write(angle);
    delay(speed);
  }
  digitalWrite(ledPinGreen, HIGH);
  digitalWrite(ledPinRed, LOW);
}
/*
============================================================================================
  FUNCTION: displayProceedMessage - displays the proceed message
  PARAMETERS: maxCycles (default is 3) - the maximum cycle count for displaying the arrows.
  Adjust for longer or shorter cycles.
  speed (default is 100) - sets the speed of the arrows being displayed.
  Higher - slower
  Lower - faster
============================================================================================
*/
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
/* 
=====================================================================================================
  FUNCTION: gateClose - closes the servo gate.
  PARAMETERS: speed (default is 20) - sets the speed through the delay.
  Higher - slower
  Lower - faster
=====================================================================================================
*/
void gateClose(int speed = 20) {
  for (int angle = 90; angle >= 0; angle--) {
    myServo.write(angle);
    delay(speed);
  }
}
/*
============================================================================================================
  FUNCTION: displayClosingMessage - displays the closing message, turns on red LED and turns off green LED.
  PARAMETERS: none
============================================================================================================
*/
void displayClosingMessage(void) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Closing...");
}
/*
=======================================================================
  FUNCTION: unauthorizedSequence - closes servo gate, turns on red LED, 
  and displays a message when unauthorized card is detected.
  PARAMETERS: none
=======================================================================
*/
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
  // if new RFID tag is near the reader & card serial is read
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String cardUID = "";
    for (byte i = 0; i < rfid.uid.size; i++) {  // decodes UID
      cardUID += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
      cardUID += String(rfid.uid.uidByte[i], HEX);
    }
    Serial.print("Card UID:  ");
    Serial.println(cardUID);
    // if the RFID tag matches predefined tag
    if (cardUID.equals(predefinedCardUID)) {
      displayOpeningMessage();
      gateOpen(); // parameters: (speed) default: (20)
      displayProceedMessage(); // parameters: (maxCycle, arrowSpeed) default: (3, 100)
      displayClosingMessage(); 
      gateClose(); // parameters: (speed) default: (20)
    } else {
      unauthorizedSequence();
    }
    delay(2000);  // 2s delay before reading card again
    while (rfid.PICC_IsNewCardPresent()) {
      delay(100);
    }
  } else {
    idleSequence();
  }
}