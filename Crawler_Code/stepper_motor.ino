void stepper_setup(){
  
  pinMode(right_stepper_pin[0], OUTPUT);
  pinMode(right_stepper_pin[1], OUTPUT);
  pinMode(right_stepper_pin[2], OUTPUT);

  pinMode(left_stepper_pin[0], OUTPUT);
  pinMode(left_stepper_pin[1], OUTPUT);
  pinMode(left_stepper_pin[2], OUTPUT);

}


void move_bot(){

   motor1_speed = bot_speed + bot_direction + error_direction;
   motor2_speed = bot_speed -  bot_direction - error_direction;

  for(int i = 0 ; i<= 5 ; i++ )
  {
  if(motor1_speed > 10){
    digitalWrite(right_stepper_pin[1],HIGH);

    digitalWrite(right_stepper_pin[0],HIGH);
    delayMicroseconds(1300 - abs(motor1_speed));  // 300 microsecond 24 rpm  30 rpm. 230 
    digitalWrite(right_stepper_pin[0],LOW);


  }
  else if (motor1_speed < -10 ){
    digitalWrite(right_stepper_pin[1],LOW);
    digitalWrite(right_stepper_pin[0],HIGH);
    delayMicroseconds(1300 - abs(motor1_speed));  // 300 microsecond 24 rpm  30 rpm. 230 
    digitalWrite(right_stepper_pin[0],LOW);

  }
  else{
    delayMicroseconds(300);
  }

if(motor2_speed > 10){
    digitalWrite(left_stepper_pin[1],LOW);
    digitalWrite(left_stepper_pin[0],HIGH);
    delayMicroseconds(1300 - abs(motor2_speed));  // 300 microsecond 24 rpm  30 rpm. 230 
    digitalWrite(left_stepper_pin[0],LOW);


  }
  else if (motor2_speed < -10 ){
    digitalWrite(left_stepper_pin[1],HIGH);
    digitalWrite(left_stepper_pin[0],HIGH);
    delayMicroseconds(1300 - abs(motor2_speed));  // 300 microsecond 24 rpm  30 rpm. 230 
    digitalWrite(left_stepper_pin[0],LOW);

  }
  else{
    delayMicroseconds(300);
  }

  }



}