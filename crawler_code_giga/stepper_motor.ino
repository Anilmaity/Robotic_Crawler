void stepper_setup() {

  pinMode(right_stepper_pin[0], OUTPUT);
  pinMode(right_stepper_pin[1], OUTPUT);
  pinMode(right_stepper_pin[2], OUTPUT);

  pinMode(left_stepper_pin[0], OUTPUT);
  pinMode(left_stepper_pin[1], OUTPUT);
  pinMode(left_stepper_pin[2], OUTPUT);
}


void move_bot() {
  error_direction = 0;
  motor1_speed = bot_speed + bot_direction + error_direction;
  motor2_speed = bot_speed - bot_direction - error_direction;

  if (motor1_speed > 500) {
    motor1_speed = 500;
  } else if (motor1_speed < -500) {
    motor1_speed = -500;
  }


  if (motor2_speed > 500) {
    motor2_speed = 500;
  } else if (motor2_speed < -500) {
    motor2_speed = -500;
  }

  if (motor1_speed > 10) {
    digitalWrite(right_stepper_pin[1], HIGH);
    total_steps +=1;
  } else if (motor1_speed < -10) {
    digitalWrite(right_stepper_pin[1], LOW);
  }


  if (motor2_speed > 10) {
    digitalWrite(left_stepper_pin[1], LOW);

  } else if (motor2_speed < -10) {
    digitalWrite(left_stepper_pin[1], HIGH);
  }

  if (abs(motor1_speed) > 10) {
    digitalWrite(right_stepper_pin[0], HIGH);
    total_steps +=1;
  }
  if (abs(motor2_speed) > 10) {
    digitalWrite(left_stepper_pin[0], HIGH);
  }


  delayMicroseconds(speed_setting - abs(motor1_speed));  // 300 microsecond 24 rpm  30 rpm. 230

  digitalWrite(right_stepper_pin[0], LOW);
  digitalWrite(left_stepper_pin[0], LOW);

  delayMicroseconds(speed_setting - abs(motor1_speed));


}