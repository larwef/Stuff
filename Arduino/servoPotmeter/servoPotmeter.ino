#include <Servo.h>

Servo servo;

int sensorPin = 5;
int servoPin = 3;

int sensorValue = 0;
int possition = 0;

void setup() {
  servo.attach(servoPin); 
}

void loop() {
  sensorValue = analogRead(sensorPin);
  possition = map(sensorValue, 0, 1023, 0, 179);
  servo.write(possition);
  delay(50);
}
