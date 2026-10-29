int potPin = A2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 0, 10000);
  Serial.print("Estimated resistance: ");
  Serial.print(potValue);
  Serial.println(" ohms");
  delay(300);
}
