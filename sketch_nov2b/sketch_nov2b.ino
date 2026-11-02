const int xAxis = A0;
const int yAxis = A1;

const int X_CENTER = 510;
const int Y_CENTER = 516;

const int DEAD_ZONE = 20;

int normalizeAxis(int value, int center) {
  if (abs(value - center) <= DEAD_ZONE) {
    return 0;
  }

  if (value > center) {
    return map(value, center + DEAD_ZONE, 1023, 0, 100);
  }
  else {
    return map(value, center - DEAD_ZONE, 0, 0, -100);
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int xVal = analogRead(xAxis);
  int yVal = analogRead(yAxis);

  int xPosition = normalizeAxis(xVal, X_CENTER);
  int yPosition = normalizeAxis(yVal, Y_CENTER);

  Serial.print("X: ");
  Serial.print(xPosition);

  Serial.print(" | Y: ");
  Serial.println(yPosition);

  delay(100);
}