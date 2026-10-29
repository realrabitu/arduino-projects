double previousMillis = 0;
double waitMillis = 0;
int intervalMillis = 1000;
int minsElapsed = 0, secsElapsed = 0, hoursElapsed = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (millis() - previousMillis >= intervalMillis) {
    previousMillis += intervalMillis;
    secsElapsed++;
    if (secsElapsed >= 60) {
      secsElapsed = 0;
      minsElapsed++;
    }
    if (minsElapsed >= 60) {
      minsElapsed = 0;
      hoursElapsed++;
    }
    Serial.print("Time elapsed: ");
    Serial.print(hoursElapsed);
    Serial.print("h ");
    Serial.print(minsElapsed);
    Serial.print("m ");
    Serial.print(secsElapsed);
    Serial.println("s");

  } else if (millis() - waitMillis >= intervalMillis / 4) {
    waitMillis += 250;
    Serial.println(" waiting...");
  }
}