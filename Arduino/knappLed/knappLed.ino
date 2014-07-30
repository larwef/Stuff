int ledPin = 3;
int btnPin = 2;

void setup() { 
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() {
  if (digitalRead(btnPin) == LOW) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPin, HIGH);
      delay(1000);
      digitalWrite(ledPin, LOW);
      delay(1000);
    }
  }
}
