int motorPin1 = 2; 
int motorPin2 = 3; 
int enable = 5;    
int potPin = A0;

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
  analogWrite(enable, potValue);
  /*for (int i = 0; i <= 255; i++) {
    analogWrite(enable, i);
    Serial.println(i);
    delay(20);
  }
  delay(6500);
  for (int i = 255; i >= 0; i--) {
    analogWrite(enable, i);
    Serial.println(i);
    delay(20);
  }*/
  
}
  