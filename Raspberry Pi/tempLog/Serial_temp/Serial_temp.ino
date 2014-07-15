int tempPin = 5;

void setup() {
        Serial.begin(9600);
}

void loop() {
        if (Serial.available() > 0) {
          float temp = ((analogRead(tempPin)*(0.004882814)) - 0.478)*100;
          Serial.read();
          Serial.println(temp);
        }
        delay(100);
}
