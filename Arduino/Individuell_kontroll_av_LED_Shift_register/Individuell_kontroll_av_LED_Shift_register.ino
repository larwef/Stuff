// "Individuell kontroll" av LED med shift register.
// Begynner på 0, slutter på 7. 0 er lengst vekk fra "måneformen" (output pin Q7)

int ser = 2;
int clock = 3;
int latch = 4;

boolean registers[8];

void setup(){
  pinMode(ser, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  
  clearRegisters();
  writeRegisters();
}

void loop(){
  for(int i = 0; i < 8; i++){
    setRegister(i, HIGH);
    writeRegisters();
    delay(500);
    setRegister(i, LOW);
    writeRegisters();
  }
}

void setRegister(int index, int value){
  registers[index] = value;
}

void writeRegisters(){
  digitalWrite(latch, LOW);

  for(int i = 0; i < 8; i++){
    digitalWrite(clock, LOW);

    int val = registers[i];

    digitalWrite(ser, val);
    digitalWrite(clock, HIGH);
  }
  digitalWrite(latch, HIGH);
}

void clearRegisters(){
  for(int i = 0; i < 8; i++){
     registers[i] = LOW;
  }
}
