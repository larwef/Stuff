int sensorPin = 0;
int ledPin = 3;

int sensorValue = 0;

void setup() {
   Serial.begin(9600);
   pinMode(ledPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(ledPin, sensorValue);
  Serial.println(sensorValue);
}
