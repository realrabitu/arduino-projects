int motorPin1 = 7; 
int motorPin2 = 8; 
int enable = 6;    
int potPin = A2;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
}

void loop() {
  int potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 255, 0);
  Serial.println("Speed: ");
  Serial.println(potValue);
  analogWrite(enable, potValue);
  delay(100);
}
  /*for (int i = 0; i <= 255; i++) {
    analogWrite(enable, i);
    delay(20);
  }
  delay(6500);
  for (int i = 255; i >= 0; i--) {
    analogWrite(enable, i);
    delay(20);
  }*/