double previousMillis = 0;
int interval = 1000;
int minsElapsed = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int secsElapsed = previousMillis / 1000;
  if (millis() - previousMillis >= interval) {
    previousMillis += interval;
    Serial.print("Time elapsed: ");
    Serial.print(minsElapsed);
    Serial.print("m ");
    Serial.print(secsElapsed);
    Serial.println("s");
    
  }
  
  
}
