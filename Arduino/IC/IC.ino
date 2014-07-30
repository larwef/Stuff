// IC

int data = 2;
int clock = 3;
int latch = 4;

void setup(){
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT); 
}

void loop(){
  int delayTime = 500  ;
  for(int i = 0; i < 256; i++){
    updateLeds(i);
    delay(delayTime);
  } 
}

void updateLeds(int value){
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, value);
  digitalWrite(latch, HIGH);
}
