void motorsetup(){


  // TCCR4B = TCCR4B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz on pin 3 (Timer 4)
  // TCCR4A = TCCR4A & B00111111 | B10100000; // set COM4A1 and COM4B1 to enable PWM on pin 3 and pin 4

    pinMode(right_motor_pin[0], OUTPUT);
  pinMode(right_motor_pin[1], OUTPUT);
  pinMode(left_motor_pin[0], OUTPUT);
  pinMode(left_motor_pin[1], OUTPUT);

}



void move_bot(){

  int m1 = bot_speed + bot_direction;
  int m2 = bot_speed - bot_direction;
  Serial.println(String(bot_speed)+ " " +String(bot_direction) + " " + String(m1) + " " + String(m2) + " " + loop_time);


  if (m1 > 20) {
    digitalWrite(right_motor_pin[0], HIGH);
    analogWrite(right_motor_pin[1], abs(m1));
    
  } 
  else if(m1 < -20) {
    digitalWrite(right_motor_pin[0], LOW);
    analogWrite(right_motor_pin[1], abs(m2));
  }
  else
  {
    digitalWrite(right_motor_pin[0], HIGH);
    analogWrite(right_motor_pin[1], 0); 
  }


  if (m2 > 20) {
    digitalWrite(left_motor_pin[0], HIGH);
    analogWrite(left_motor_pin[1], abs(m1));
    
  } 
  else if(m2 < -20) {
    digitalWrite(left_motor_pin[0], LOW);
    analogWrite(left_motor_pin[1], abs(m2));
  }
  else
  {
    digitalWrite(left_motor_pin[0], HIGH);
    analogWrite(left_motor_pin[1], 0); 
  }
  delay(50);

}