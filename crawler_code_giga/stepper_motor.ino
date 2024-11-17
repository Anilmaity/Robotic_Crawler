int min_speed = 5;

void stepper_setup() {

  pinMode(right_stepper_pin[0], OUTPUT);
  pinMode(right_stepper_pin[1], OUTPUT);
  pinMode(right_stepper_pin[2], OUTPUT);

  pinMode(left_stepper_pin[0], OUTPUT);
  pinMode(left_stepper_pin[1], OUTPUT);
  pinMode(left_stepper_pin[2], OUTPUT);
}


void auto_correct() {
  float error_value = -(target_pitch_angle - pitch);
  if (auto_pitch == true) {
   
   i_error += error_value * 0.0001;
   d_error = (previous_error - error_value)*10;
   p_error = error_value * 25;
   error_direction = p_error + d_error + i_error;
   previous_error = error_value;
   
  } else {
    error_direction = 0;
    i_error =0;
    previous_error = 0;
  }
}

void move_bot() {
  ibus_loop();
  auto_correct();
  motor1_speed = bot_speed + bot_direction + error_direction;
  motor2_speed = bot_speed - bot_direction - error_direction;

  // Constrain motor speeds within the limit [-500, 500]
  motor1_speed = constrain(motor1_speed, -500, 500);
  motor2_speed = constrain(motor2_speed, -500, 500);

  // Calculate the number of loops based on the speed (10 loops at speed 500)
  int motor1_loops = map(abs(motor1_speed), 0, 500, 0, 10);  // 0 to 10 loops for motor 1
  int motor2_loops = map(abs(motor2_speed), 0, 500, 0, 10);  // 0 to 10 loops for motor 2
  
  
  // Determine the maximum number of loops needed
  int max_loops = max(motor1_loops, motor2_loops);

  // Loop according to the maximum number of loops
  for (int i = 0; i < max_loops; i++) {
    // Handle motor 1 direction and stepping if it still needs more loops
    if (i < motor1_loops) {
      // Apply no_360 logic: stop motor1 if motor2 is moving too fast in the opposite direction
      if (no_360 && motor2_speed < 0 && motor1_speed > 0) {
        motor1_speed = 0;
      }

      if (motor1_speed > 0) {
        digitalWrite(right_stepper_pin[1], HIGH);  // Set direction forward
      } else {
        digitalWrite(right_stepper_pin[1], LOW);  // Set direction reverse
      }

      if (abs(motor1_speed) > min_speed) {
        digitalWrite(right_stepper_pin[0], HIGH);              // Step motor 1
        delayMicroseconds(speed_setting - abs(motor1_speed));  // Speed control for motor 1
        digitalWrite(right_stepper_pin[0], LOW);
        delayMicroseconds(speed_setting - abs(motor1_speed));  // Pause between steps
        total_steps += 1;
      }
    }

    // Handle motor 2 direction and stepping if it still needs more loops
    if (i < motor2_loops) {
      // Apply no_360 logic: stop motor2 if motor1 is moving too fast in the opposite direction
      if (no_360 && motor1_speed < 0 && motor2_speed > 0) {
        motor2_speed = 0;
      }

      if (motor2_speed > 0) {
        digitalWrite(left_stepper_pin[1], LOW);  // Set direction forward
      } else {
        digitalWrite(left_stepper_pin[1], HIGH);  // Set direction reverse
      }

      if (abs(motor2_speed) > min_speed) {
        digitalWrite(left_stepper_pin[0], HIGH);               // Step motor 2
        delayMicroseconds(speed_setting - abs(motor2_speed));  // Speed control for motor 2
        digitalWrite(left_stepper_pin[0], LOW);
        delayMicroseconds(speed_setting - abs(motor2_speed));  // Pause between steps
      }
    }
  }
}
