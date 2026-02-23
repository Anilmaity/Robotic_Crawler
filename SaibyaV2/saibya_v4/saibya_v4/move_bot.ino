
void move_bot_rc() {



    if (bot_direction >= 0) {
      if (bot_speed >= 0) {
        motor_1_speed = constrain(bot_speed, -255, 255);
        motor_2_speed = constrain(bot_speed + bot_direction, -255, 255);
      } else {

        motor_1_speed = constrain(bot_speed - bot_direction, -255, 255);
        motor_2_speed = constrain(bot_speed, -255, 255);
      }



    }



    else {
      if (bot_speed > 0) {
        motor_1_speed = constrain(bot_speed, -255, 255);
        motor_2_speed = constrain(bot_speed + bot_direction, -255, 255);
      } else {
        motor_1_speed = constrain(bot_speed - bot_direction, -255, 255);
        motor_2_speed = constrain(bot_speed, -255, 255);
      }
    }
  

  apply_pwm(M1_DIR, pwm1, -motor_1_speed);
  apply_pwm(M4_DIR, pwm4, motor_1_speed);
  apply_pwm(M2_DIR, pwm2, -motor_2_speed);
  apply_pwm(M3_DIR, pwm3, motor_2_speed);
}

// ================= APPLY PWM =================
void apply_pwm(int dir_pin, mbed::PwmOut* pwm, int target) {
  if (abs(target) > 12) {
    digitalWrite(dir_pin, target > 0 ? HIGH : LOW);
    pwm->write(abs(target) / 255.0);  // duty cycle 0.0–1.0
  } else {
    pwm->write(0.0);
  }
}



void move_bot_uart() {


  apply_pwm(M1_DIR, pwm1, -uart_m1_speed);
  apply_pwm(M4_DIR, pwm4, uart_m4_speed);
  apply_pwm(M2_DIR, pwm2, -uart_m2_speed);
  apply_pwm(M3_DIR, pwm3, uart_m3_speed);
}
