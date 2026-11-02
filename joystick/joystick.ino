const byte xAxis = A1, yAxis = A2;
const byte blueLED = 5, redLED = 6, yellowLED = 9, greenLED = 10;
void setup() {
  Serial.begin(9600);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

}

void loop() {
  int leftBrightness = 0;
  int rightBrightness = 0;
  int upBrightness = 0;
  int downBrightness = 0;
  int xVal = analogRead(xAxis);
  int yVal = analogRead(yAxis);
  Serial.print("X: "); Serial.println(xVal);
  Serial.print("Y: "); Serial.println(yVal);
  if (xVal > 520) {
    rightBrightness = map(xVal, 520, 1023, 0, 255);
  }
  else if (xVal < 505) {
    leftBrightness = map(xVal, 505, 0, 0, 255);
  }
  if (yVal < 510) {
    upBrightness = map(yVal, 510, 0, 0, 255);
  }
  else if (yVal > 520) {
    downBrightness = map(yVal, 520, 1023, 0, 255);
  }
 
  
  
  analogWrite(blueLED, rightBrightness);
  analogWrite(redLED, leftBrightness);
  analogWrite(yellowLED, downBrightness);
  analogWrite(greenLED, upBrightness);
  delay(150);
}
