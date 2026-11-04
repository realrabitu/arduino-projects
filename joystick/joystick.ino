const byte xAxis = A1, yAxis = A2;
const byte blueLED = 5, redLED = 6, yellowLED = 9, greenLED = 10;
double previousMillis = 0;
byte intervalMillis = 150;

void setup() {
  Serial.begin(9600);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

void loop() {
  byte leftBrightness = 0;
  byte rightBrightness = 0;
  byte upBrightness = 0;
  byte downBrightness = 0;
  if (millis() - previousMillis >= intervalMillis) {
    previousMillis += intervalMillis;
    short xVal = analogRead(xAxis);
    short yVal = analogRead(yAxis);
    Serial.print("X: ");
    Serial.println(xVal);
    Serial.print("Y: ");
    Serial.println(yVal);
    if (xVal > 560) {
      rightBrightness = map(xVal, 520, 1023, 0, 255);
    } else if (xVal < 505) {
      leftBrightness = map(xVal, 505, 0, 0, 255);
    }
    if (yVal < 500) {
      upBrightness = map(yVal, 510, 0, 0, 255);
    } else if (yVal > 530) {
      downBrightness = map(yVal, 520, 1023, 0, 255);
    }
    analogWrite(blueLED, rightBrightness);
    analogWrite(redLED, leftBrightness);
    analogWrite(yellowLED, downBrightness);
    analogWrite(greenLED, upBrightness);
  }
}
