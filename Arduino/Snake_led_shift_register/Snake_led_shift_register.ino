// Snake LEDS shift register
// Litt problemer med ground, nå(første gang den ble satt opp)
//Bare drit i ground pin 8 på shiften, så ordna det seg.

int clock = 3;
int latch = 4;

void setup(){
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
}

void loop(){
  digitalWrite(latch, HIGH);
  digitalWrite(clock,HIGH);
  delay(100);
  digitalWrite(clock,LOW);
  digitalWrite(latch, LOW);
}
