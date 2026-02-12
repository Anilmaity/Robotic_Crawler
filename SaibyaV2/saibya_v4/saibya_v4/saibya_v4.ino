#include <AlfredoCRSF.h>

// ================= CONFIG =================
#define MAX_CHANNELS 8

// Relay Pins
#define RELAY1_PIN 38
#define RELAY2_PIN 40

// Motor Pins
int M1_PWM = 2;
int M1_DIR = 3;
int M2_PWM = 8;
int M2_DIR = 9;
int M3_PWM = 6;
int M3_DIR = 7;
int M4_PWM = 4;
int M4_DIR = 5;

// ================= CRSF =================
AlfredoCRSF crsf;

// ================= GLOBALS =================
uint16_t channels[MAX_CHANNELS];

int bot_speed = 0;
int bot_direction = 0;
int motor_1_speed = 0;
int motor_2_speed = 0;

// ================= SETUP =================
void setup() {

  Serial.begin(921600);

  // CRSF runs at 420000 baud
  Serial3.begin(CRSF_BAUDRATE);
  crsf.begin(Serial3);

  motor_setup();
}

// ================= LOOP =================
void loop() {

  static unsigned long last_motor_update = 0;
  static unsigned long last_debug = 0;

  crsf.update();

  bool rc_connected = crsf.isLinkUp();

  if (rc_connected) {

    // Read channels
    for (int i = 0; i < MAX_CHANNELS; i++) {
      channels[i] = crsf.getChannel(i + 1);
    }

    // ===== ARM SWITCH (CH6) =====
    bool armed = (channels[4] > 1400);

    // ===== RELAY CONTROL =====
    digitalWrite(RELAY1_PIN, channels[5] > 1500 ? HIGH : LOW);  // CH6
    digitalWrite(RELAY2_PIN, channels[5] > 1500 ? HIGH : LOW);  // CH7

    if (armed) {

      // ===== THROTTLE (CH2) =====
      int throttle_input = channels[1];

      if (throttle_input >= 1500) {
        float x = (float)(throttle_input - 1500) / 400.0;
        bot_speed = (int)(255.0 * x * x);
      } else {
        float x = (float)(1500 - throttle_input) / 400.0;
        bot_speed = -(int)(255.0 * x * x);
      }

      // ===== STEERING (CH1) =====
      int steer_input = channels[3];

      if (steer_input >= 1500) {
        float x = (float)(steer_input - 1500) / 400.0;
        bot_direction = (int)(255.0 * x * x);
      } else {
        float x = (float)(1500 - steer_input) / 400.0;
        bot_direction = -(int)(255.0 * x * x);
      }

    } else {
      // Not armed → motors off
      bot_speed = 0;
      bot_direction = 0;
    }

  } else {
    // ===== FAILSAFE =====
    bot_speed = 0;
    bot_direction = 0;

    digitalWrite(RELAY1_PIN, LOW);
    digitalWrite(RELAY2_PIN, LOW);
  }

  // ===== MOTOR UPDATE @ 1kHz =====
  if (micros() - last_motor_update >= 1000) {
    last_motor_update = micros();
    move_bot();
  }

  // ===== DEBUG =====
  if (millis() - last_debug > 100) {
    last_debug = millis();
    send_data();
  }
}

// ================= MOTOR LOGIC =================
void move_bot() {

  motor_1_speed = bot_speed - bot_direction;
  motor_2_speed = bot_speed + bot_direction;

  motor_1_speed = constrain(motor_1_speed, -255, 255);
  motor_2_speed = constrain(motor_2_speed, -255, 255);

  apply_pwm(M1_DIR, M1_PWM, motor_1_speed);
  apply_pwm(M3_DIR, M3_PWM, motor_1_speed);
  apply_pwm(M2_DIR, M2_PWM, motor_2_speed);
  apply_pwm(M4_DIR, M4_PWM, motor_2_speed);
}

void apply_pwm(int dir_pin, int pwm_pin, int target) {

  if (abs(target) > 12) {
    digitalWrite(dir_pin, target > 0 ? HIGH : LOW);
    analogWrite(pwm_pin, abs(target));
  } else {
    analogWrite(pwm_pin, 0);
  }
}

// ================= SETUP MOTORS & RELAYS =================
void motor_setup() {

  pinMode(M1_DIR, OUTPUT); pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT); pinMode(M2_PWM, OUTPUT);
  pinMode(M3_DIR, OUTPUT); pinMode(M3_PWM, OUTPUT);
  pinMode(M4_DIR, OUTPUT); pinMode(M4_PWM, OUTPUT);

  analogWriteResolution(8);        // 0–255 like normal


  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  digitalWrite(M1_DIR, LOW);
  digitalWrite(M2_DIR, LOW);
  digitalWrite(M3_DIR, LOW);
  digitalWrite(M4_DIR, LOW);


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
