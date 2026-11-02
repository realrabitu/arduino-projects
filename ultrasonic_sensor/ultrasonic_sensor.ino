const byte trigPin = 3, echoPin = 2;
const byte ledPin = 12;
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
    if (distance <= 5) {
      digitalWrite(ledPin, HIGH);
      Serial.println("Obstacle detected!");
    }
    else {
      digitalWrite(ledPin, LOW);
    }
  }
  
  

}
