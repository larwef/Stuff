// Device number can be read in the Pololu program thingy. Usualy 12.

int device = 12;

// Target usualy 4000-8000
void set_target(int servo,int target){
  Serial.write(170); //Start byte
  Serial.write(device); //Device number
  Serial.write(4); //Command number
  Serial.write(servo); //Servo number
  Serial.write(target & 127);  
  Serial.write((target >> 7) & 127);
}
//Ca 100 min - 0 max speed
void set_speed(int servo, int vel){
  Serial.write(170); //Start byte
  Serial.write(device); //Device number
  Serial.write(7); //Command number
  Serial.write(servo); //Servo number
  Serial.write(vel & 127);  
  Serial.write((vel >> 7) & 127);
}
//255 min - 0 max
void set_acc(int servo, int acc){
  Serial.write(170); //Start byte
  Serial.write(device); //Device number
  Serial.write(9); //Command number
  Serial.write(servo); //Servo number
  Serial.write(acc & 127);  
  Serial.write((acc >> 7) & 127);
}
//Sets the target to home (home is chosen in Pololu program)
void go_home(int servo){
 Serial.write(170); //Start byte
 Serial.write(device); //Device number
 Serial.write(34); //Command number
}

