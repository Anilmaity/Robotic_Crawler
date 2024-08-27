void brakesetup(){

  pinMode(brake_pin[0], OUTPUT);
  pinMode(brake_pin[1], OUTPUT);
  pinMode(brake_dir_pin[0], OUTPUT);
  pinMode(brake_dir_pin[1], OUTPUT);
  // pinMode(brake_pin[4], OUTPUT);
  // pinMode(brake_pin[5], OUTPUT);
  // pinMode(brake_pin[6], OUTPUT);
    digitalWrite(brake_dir_pin[0], HIGH);
  digitalWrite(brake_dir_pin[1], HIGH);
}

void braking(){


  analogWrite(brake_pin[0], brake);
  analogWrite(brake_pin[1], brake);

  
  }