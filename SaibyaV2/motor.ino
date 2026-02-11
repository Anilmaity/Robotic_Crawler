



void throttle_setup() {
  pinMode(throttle_pin, OUTPUT);
  pinMode(Reverse_pin, OUTPUT);
  pinMode(Brake_pin, OUTPUT);

  digitalWrite(Reverse_pin, HIGH);
  digitalWrite(Brake_pin, HIGH);
}

void throttling() {

  if (input_throttle > int(initial_throttle/2)) {
    digitalWrite(Brake_pin, LOW);
    // delay(1);
    digitalWrite(Reverse_pin, HIGH);


  } else if(input_throttle < int(-initial_throttle_backward/2)) {
      digitalWrite(Brake_pin, LOW);
          // delay(1);
      digitalWrite(Reverse_pin, LOW);

  }
  else{
        digitalWrite(Brake_pin, HIGH);

  }


  if (throttle > 0) {
    if (throttle > input_throttle ) {

      
      if(input_throttle < initial_throttle){

        if(input_throttle < -initial_throttle_backward/5 ){
            input_throttle = input_throttle + speed_increase_rate_forward;

        }
        else{
            input_throttle = initial_throttle;
        }

      }
      else if(input_throttle < 0){
        input_throttle =  0 ;
      }
      else if ( input_throttle < 100){
       input_throttle = input_throttle + speed_increase_rate_forward;
      }
      else
      {
        input_throttle = input_throttle + speed_increase_rate_forward;

      }

    } else if (throttle <= input_throttle) {
      input_throttle = input_throttle - speed_decrease_rate;
    } else {
      input_throttle = 0;
    }

  } else if(throttle < 0){

    
    if(input_throttle > -initial_throttle_backward){
      
      if(input_throttle > initial_throttle_backward/5){

        input_throttle = input_throttle - speed_increase_rate_backward; //

      }
      else{
        input_throttle = -initial_throttle_backward;
      }
      }
    else if (throttle < input_throttle) {
      if(input_throttle > 0){
        input_throttle = 0 ;
      }
      else if(input_throttle > -100){
       input_throttle = input_throttle - speed_increase_rate_backward; //

      }
      else{
       input_throttle = input_throttle - speed_increase_rate_backward; //
      }

    } else if (throttle >= input_throttle) {
      input_throttle = input_throttle + speed_decrease_rate;
    } 
  }
  else{
    if(input_throttle > 0){
      input_throttle = input_throttle - speed_decrease_rate;
    }
    else if(input_throttle < 0)
    {
      input_throttle = input_throttle + speed_decrease_rate;
    }
    else{
      input_throttle = 0;
    }
  }
  

  if (abs(throttle) > initial_throttle_backward) {

    // pwm->pulsewidth_us(abs(int(input_throttle)));
    analogWrite(throttle_pin, abs(input_throttle));

  } else {
    
    analogWrite(throttle_pin, abs(input_throttle));

  }
}