//Alarm, bruk 10k ohm motstand.

int photoPin = 0;
int ledPin = 13;
int lydPin = 9;

void setup(){
 pinMode(ledPin, OUTPUT);
 pinMode(lydPin, OUTPUT);
 
 for(int i = 0; i < 3; i++){
   digitalWrite(ledPin, HIGH);
   delay(500);
   digitalWrite(ledPin, LOW);
   delay(500);
 }
}

void loop(){
  int lightLevel = analogRead(photoPin);
  lightLevel = map(lightLevel, 0, 900, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
  
  while(lightLevel < 200){
    digitalWrite(lydPin, HIGH);
    delayMicroseconds(3038);
    digitalWrite(lydPin, LOW);
    delayMicroseconds(3038);
     
    digitalWrite(ledPin, LOW);
    break;
  }
   digitalWrite(ledPin, HIGH);
}
