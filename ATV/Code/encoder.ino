void encoder_setup() {

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);


  
}

void encoder_read(){

  binStr = 
    String(digitalRead(A0)) +
    String(digitalRead(A1)) +
    String(digitalRead(A2)) +
    String(digitalRead(A3)) +
    String(digitalRead(A4)) +
    String(digitalRead(A5)) +
    String(digitalRead(A6)) +
    String(digitalRead(A7)) +
    String(digitalRead(11)) +
    String(digitalRead(12));


int H = (digitalRead(11) << 1) | digitalRead(12);  // hundreds digit 0–3
  int T = (digitalRead(A7) << 3) |
          (digitalRead(A6) << 2) |
          (digitalRead(A5) << 1) |
           digitalRead(A4);                           // tens digit 0–9
  int O = (digitalRead(A3) << 3) |
          (digitalRead(A2) << 2) |
          (digitalRead(A1) << 1) |
           digitalRead(A0);                           // ones digit 0–9

  int angle = H * 100 + T * 10 + O - 105 ;  // decimal angle

  sensorValue = angle ;


}



void sterring_setup() {

  pinMode(S_DIR, OUTPUT);
  // pinMode(S_PWM, OUTPUT);
  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);   // configure channel
  ledcAttachPin(S_PWM, PWM_CHANNEL);         // attach pin to channel
  // ledcAttach(S_PWM, PWM_FREQUENCY, PWM_RESOLUTION);


  
}



void sterring_loop() {

  if(sensorValue != 360){

  
  error_sterring = sensorValue - sterring_value;

  

  if (abs(error_sterring) > 4) {
    if (error_sterring > 0) {
      digitalWrite(S_DIR, HIGH); // direction right or left
    }
    else {
      digitalWrite(S_DIR, LOW);
    }
    // if(abs(error_sterring) < 20 )
    // {
    //   // analogWrite(S_PWM,abs(100)); // max speed for motor
    
    // ledcWrite(PWM_CHANNEL, abs(p_sterring*error_sterring));  // 50%

    // }
    // else{
      // analogWrite(S_PWM,abs(p_sterring*error_sterring));
    ledcWrite(PWM_CHANNEL, abs(p_sterring*error_sterring));  // 50%

      // }

    // if(abs(error_sterring) < 40 ){
    //     sterring_pwm ->pulsewidth_us(100);
    //     delayMicroseconds(abs(error_sterring)*100);
    //   }
    //   else
    //   {
    //     sterring_pwm ->pulsewidth_us(100);
    //     delayMicroseconds(1000);
    //   }

  } else {
    //sterring_pwm ->pulsewidth_us(0);
    // analogWrite(S_PWM,0); // 0 pwm signal
    ledcWrite(PWM_CHANNEL, 0);  // 50%


  }
  }
}
