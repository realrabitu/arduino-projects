int potPin = A1;
int ledPin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(ledPin, potValue);
  Serial.println(potValue);
  delay(50);
}
