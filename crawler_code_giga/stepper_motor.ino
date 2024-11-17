int min_speed = 5;
#include <mbed.h>

PinName right = digitalPinToPinName(D8);
PinName left = digitalPinToPinName(D9);
float m1s = 1000;
float m2s = 1000;

mbed::PwmOut* pwm_right = new mbed::PwmOut(right);
mbed::PwmOut* pwm_left = new mbed::PwmOut(left);

void stepper_setup() {

  //pinMode(right_stepper_pin[0], OUTPUT);
  pinMode(right_stepper_pin[1], OUTPUT);
  pinMode(right_stepper_pin[2], OUTPUT);

  //pinMode(left_stepper_pin[0], OUTPUT);
  pinMode(left_stepper_pin[1], OUTPUT);
  pinMode(left_stepper_pin[2], OUTPUT);

  pwm_right->period_us(1000);  //1kHz
  pwm_right->pulsewidth_us(500);
  pwm_right->write(0);


  pwm_left->period_us(1000);  //1kHz
  pwm_left->pulsewidth_us(500);
  pwm_left->write(0);  //1kHz
}


void auto_correct() {
  float error_value = -(target_pitch_angle - pitch);
  if (auto_pitch == true) {

    i_error += error_value * 0.0001;
    d_error = (previous_error - error_value) * 10;
    p_error = error_value * 25;
    error_direction = p_error + d_error + i_error;
    previous_error = error_value;

  } else {
    error_direction = 0;
    i_error = 0;
    previous_error = 0;
  }
}

void move_bot() {
  ibus_loop();
  auto_correct();
  motor1_speed = bot_speed + bot_direction + error_direction;
  motor2_speed = bot_speed - bot_direction - error_direction;

  // Constrain motor speeds within the limit [-500, 500]
  motor1_speed = constrain(motor1_speed, -1000, 1000);
  motor2_speed = constrain(motor2_speed, -1000, 1000);



  // Apply no_360 logic: stop motor1 if motor2 is moving too fast in the opposite direction
  if (no_360 && motor2_speed < 0 && motor1_speed > 0) {
    motor1_speed = 0;
  }

  if (motor1_speed > 0) {
    digitalWrite(right_stepper_pin[1], HIGH);  // Set direction forward
  } else {
    digitalWrite(right_stepper_pin[1], LOW);  // Set direction reverse
  }



  // Apply no_360 logic: stop motor2 if motor1 is moving too fast in the opposite direction
  if (no_360 && motor1_speed < 0 && motor2_speed > 0) {
    motor2_speed = 0;
  }

  if (motor2_speed > 0) {
    digitalWrite(left_stepper_pin[1], LOW);  // Set direction forward
  } else {
    digitalWrite(left_stepper_pin[1], HIGH);  // Set direction reverse
  }


    if (abs(motor2_speed) > 0) {
    m2s = 11000 - abs(motor2_speed)*10;
    pwm_left->period_us(m2s);  //1kHz
    pwm_left->pulsewidth_us(250);
  }


  if (abs(motor1_speed) > 0) {
    m1s = 11000 - abs(motor1_speed)*10;
    pwm_right->period_us(m1s);  //1kHz
    pwm_right->pulsewidth_us(250);
  }






  delayMicroseconds(5000);
  pwm_right->write(0);
  pwm_left->write(0);  //1kHz
}
