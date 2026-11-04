const byte trigPin = 3, echoPin = 2;
const byte buzzerPin = 11;
const byte warningLED = 12;
long distance, duration;
double previousMillis = 0;
double previousBuzzerMillis = 0;
short intervalMillis = 200;
short buzzerInterval = 0;
bool buzzerState = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(warningLED, OUTPUT);
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
    detectObstacle();
  }
}

void detectObstacle() {
  if (distance > 25 || distance <= 0) {
    noTone(buzzerPin);
    digitalWrite(warningLED, LOW);
    return;
  }
  else if (distance <= 5) {
    Serial.println("Imminent obstacle detected.");
  }
  else if (distance <= 10) {
    Serial.println("Obstacle detected.");
  }
  else if (distance <= 25) {
    Serial.println("Possible obstacle detected.");
  }
  if (distance < 25) {
    digitalWrite(warningLED, HIGH);
  }
  
  buzzerInterval = map(distance, 0, 25, 25, 1000);
  buzzerInterval = constrain(buzzerInterval, 25, 1000);

  if (millis() - previousBuzzerMillis >= buzzerInterval) {
    previousBuzzerMillis = millis();
    buzzerState = !buzzerState;

    if (buzzerState) {
      
      tone(buzzerPin, 750, 250);
    } else {
      noTone(buzzerPin);
    }

  }
}
