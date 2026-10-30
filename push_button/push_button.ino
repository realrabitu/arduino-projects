const int button = 7;
int lastButtonState = 0;
void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(button);
  Serial.print("Button state: ");
  switch (buttonState) {
    case 0:
      Serial.println("LOW");
      break;
    case 1:
      Serial.println("HIGH");
      break;
    default:
      Serial.println("Not a valid button state.");
  }
  delay(250);
}
