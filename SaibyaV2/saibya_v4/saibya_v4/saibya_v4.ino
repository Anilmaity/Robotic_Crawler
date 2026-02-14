#include <AlfredoCRSF.h>
#include "mbed.h"
#include <crsf_protocol.h>

// ================= CONFIG =================
#define MAX_CHANNELS 8

// Relay Pins
#define RELAY1_PIN 38
#define RELAY2_PIN 40

// Motor Pins
int M1_PWM = 4; // 4
int M1_DIR = 5; // 5
int M2_PWM = 2; // 
int M2_DIR = 3;
int M3_PWM = 6;
int M3_DIR = 7;
int M4_PWM = 8;
int M4_DIR = 9;

//1432
//4321

bool skid = false;

// ================= CRSF =================
AlfredoCRSF crsf;

// ================= GLOBALS =================
uint16_t channels[MAX_CHANNELS];
int bot_speed = 0;
int bot_direction = 0;
int motor_1_speed = 0;
int motor_2_speed = 0;



String inputString = "";
bool stringComplete = false;


// ================= MBED PWM OBJECTS =================
mbed::PwmOut* pwm1;
mbed::PwmOut* pwm2;
mbed::PwmOut* pwm3;
mbed::PwmOut* pwm4;

// ================= SETUP =================
void setup() {
  // Serial.begin(921600);
  AT_Setup();
  
  Serial3.begin(CRSF_BAUDRATE);

  crsf.begin(Serial3);

  // Motor pins as outputs
  pinMode(M1_DIR, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M3_DIR, OUTPUT);
  pinMode(M4_DIR, OUTPUT);
  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);

  // Relays
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);

  // Create mbed PwmOut objects
  pwm1 = new mbed::PwmOut(digitalPinToPinName(M1_PWM));
  pwm2 = new mbed::PwmOut(digitalPinToPinName(M2_PWM));
  pwm3 = new mbed::PwmOut(digitalPinToPinName(M3_PWM));
  pwm4 = new mbed::PwmOut(digitalPinToPinName(M4_PWM));

  // Set PWM period for 20 kHz => period = 50 us
  pwm1->period_us(50);
  pwm2->period_us(50);
  pwm3->period_us(50);
  pwm4->period_us(50);

  // Start with 0% duty
  pwm1->write(0.0);
  pwm2->write(0.0);
  pwm3->write(0.0);
  pwm4->write(0.0);

}

// ================= LOOP =================
void loop() {
  static unsigned long last_motor_update = 0;
  static unsigned long last_debug = 0;

  crsf.update();
  bool rc_connected = crsf.isLinkUp();

  if (rc_connected) {
    for (int i = 0; i < MAX_CHANNELS; i++) {
      channels[i] = crsf.getChannel(i + 1);
    }

    bool armed = (channels[4] > 1400);

    handleRelay(RELAY1_PIN, channels[5]);  // CH5 is index 4
    //handleRelay(RELAY2_PIN, channels[5]);  // CH5 is index 4


    if (armed) {

    int throttle_input = channels[1];
    int steer_input    = channels[3];

    // Map CRSF range (~1000–2000) to -255 to 255
    bot_speed     = map(throttle_input, 1000, 2000, -255, 255);
    bot_direction = map(steer_input,    1000, 2000, -255, 255);

    // Optional: small deadband around center
    if (abs(bot_speed) < 10) bot_speed = 0;
    if (abs(bot_direction) < 10) bot_direction = 0;

    skid = (channels[6] > 1400);





    } else {
      bot_speed = 0;
      bot_direction = 0;
    }
  } else {
    bot_speed = 0;
    bot_direction = 0;
    // digitalWrite(RELAY1_PIN, LOW);
    // digitalWrite(RELAY2_PIN, LOW);
  }

  // Motor update @ 1kHz
  if (micros() - last_motor_update >= 1000) {
    last_motor_update = micros();
    move_bot();
  }

  // Debug
  // if (millis() - last_debug > 100) {
  //   last_debug = millis();
  //   send_data();
  // }

    if (stringComplete) {
    processATCommand(inputString);
    inputString = "";
    stringComplete = false;
  }

}

// ================= MOTOR LOGIC =================

void move_bot() {

  if (skid) {


    motor_1_speed = constrain(bot_speed + bot_direction, -255, 255);
    motor_2_speed = constrain(bot_speed - bot_direction, -255, 255);

  }

  else {

    if (bot_direction > 0) {
      motor_1_speed = constrain(bot_speed + bot_direction , -255, 255);
      motor_2_speed = constrain(bot_speed , -255, 255);

    } 

    

    else {
      motor_1_speed = constrain(bot_speed, -255, 255);
      motor_2_speed = constrain(bot_speed - bot_direction , -255, 255);
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

// ================= DEBUG =================
void send_data() {
  Serial.print("CH1: ");
  Serial.print(channels[3]);
  Serial.print(" | CH2: ");
  Serial.print(channels[1]);
  Serial.print(" | Armed: ");
  Serial.print(channels[5] > 1400);
  Serial.print(" | Speed: ");
  Serial.print(bot_speed);
  Serial.print(" | Dir: ");
  Serial.print(bot_direction);
  Serial.print(" | Left: ");
  Serial.print(motor_1_speed);
  Serial.print(" | Right: ");
  Serial.println(motor_2_speed);
}
