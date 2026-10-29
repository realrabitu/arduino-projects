const int trigPin = 12, echoPin = 13;
const int ledPin = 9;
int brightness = 0;
long distance, duration;
double previousMillis = 0;
int intervalMillis = 200;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // Use of non-blocking delay
  if (millis() - previousMillis >= intervalMillis) { 
    previousMillis += intervalMillis;
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 20000UL);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  brightness = constrain(map(distance, 0, 200, 0, 255),0,255);
  analogWrite(ledPin, brightness);

}
