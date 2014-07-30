int ledPin = 9;
int sensorPin = 0;

void setup(){
  pinMode(ledPin, OUTPUT);
}

void loop(){
  int value = analogRead(sensorPin)/4;
  analogWrite(ledPin, value); 
}
