// === CONFIGURATION ===
#define PPM_PIN 21  // Pin for PPM signal input (INT0-INT5 on Mega)
#define MAX_CHANNELS 8
#define PPM_SYNC_GAP 3000  // µs - Sync pulse threshold

//     FRONT
//    2 ---  1 
//    |.  .|
//    4 ---  3

// Motor Pins (DMC60 PWM inputs)
int M1_PWM = 2;  // Left-front (DMC60 PWM input)
int M1_DIR = 3;  // Left-front direction
int M2_PWM = 5;  // Right-front (DMC60 PWM input)
int M2_DIR = 4;  // Right-front direction
int M3_PWM = 6;  // Left-rear (DMC60 PWM input)
int M3_DIR = 7;  // Left-rear direction
int M4_PWM = 8;  // Right-rear (DMC60 PWM input)
int M4_DIR = 9;  // Right-rear direction

// === GLOBAL VARIABLES ===
volatile uint16_t ppm_channels[MAX_CHANNELS] = {0};
volatile uint8_t ppm_index = 0;
volatile unsigned long last_interrupt_time = 0;
volatile unsigned long last_signal_time = 0;
bool ppm_signal_lost = true;

int bot_speed = 0;      // Throttle input (-255 to 255)
int bot_direction = 0;  // Steering input (-255 to 255)
int motor_1_speed = 0;  // Left side target speed
int motor_2_speed = 0;  // Right side target speed

// === SETUP ===
void setup() {
  Serial.begin(921600);
  ppm_setup();
  motor_setup();
}

// === MAIN LOOP ===
void loop() {
  static unsigned long last_motor_update = 0;
  static unsigned long last_debug = 0;
  static unsigned long last_rc_check = 0;
  bool rc_connected = true;

  // Safe copy of PPM channels
  uint16_t channels_copy[MAX_CHANNELS];
  noInterrupts();
  memcpy(channels_copy, ppm_channels, sizeof(channels_copy));
  interrupts();

  // Check signal timeout every 100ms
  if (millis() - last_rc_check > 100) {
    rc_connected = (millis() - last_signal_time < 500);
    last_rc_check = millis();
  }

  // Update speed/direction based on RC
if (rc_connected) {
    if (channels_copy[2] >= 1000 && channels_copy[2] <= 2000) {
      // Exponential mapping for throttle
      int throttle_input = channels_copy[2];  // Pulse width in µs
      if (throttle_input >= 1500) {
        // Positive range (1500 to 1905 µs → 0 to 255)
        float x = (float)(throttle_input - 1500) / (1905 - 1500);  // Normalize 0 to 1
        bot_speed = (int)(255.0 * x * x);  // Quadratic mapping
      } else {
        // Negative range (1095 to 1500 µs → -255 to 0)
        float x = (float)(1500 - throttle_input) / (1500 - 1095);  // Normalize 0 to 1
        bot_speed = -(int)(255.0 * x * x);  // Quadratic mapping
      }
    }
    if (channels_copy[0] >= 1000 && channels_copy[0] <= 2000) {
      // Exponential mapping for steering
      int steer_input = channels_copy[0];  // Pulse width in µs
      if (steer_input >= 1500) {
        // Positive range (1500 to 1905 µs → 0 to 255, right)
        float x = (float)(steer_input - 1500) / (1905 - 1500);  // Normalize 0 to 1
        bot_direction = (int)(255.0 * x * x);  // Quadratic mapping
      } else {
        // Negative range (1095 to 1500 µs → -255 to 0, left)
        float x = (float)(1500 - steer_input) / (1500 - 1095);  // Normalize 0 to 1
        bot_direction = -(int)(255.0 * x * x);  // Quadratic mapping
      }
    }
  } else {
    bot_speed = 0;
    bot_direction = 0;
  }

  // Update motors at 1kHz
  if (micros() - last_motor_update >= 1000) {
    last_motor_update = micros();
    move_bot();
  }

  // Debug print every 10ms
  if (millis() - last_debug > 10) {
    last_debug = millis();
    send_data(channels_copy);
  }
}

// === PPM INTERRUPT SETUP ===
void ppm_setup() {
  pinMode(PPM_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PPM_PIN), ppm_interrupt, FALLING);
}

void ppm_interrupt() {
  unsigned long now = micros();
  unsigned long duration = now - last_interrupt_time;
  last_interrupt_time = now;

  if (duration > PPM_SYNC_GAP) {
    ppm_index = 0;
  } else if (ppm_index < MAX_CHANNELS) {
    ppm_channels[ppm_index++] = duration;
    last_signal_time = millis();
    ppm_signal_lost = false;
  }
}

// === MOTOR SETUP ===
void motor_setup() {
  pinMode(M1_DIR, OUTPUT); pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT); pinMode(M2_PWM, OUTPUT);
  pinMode(M3_DIR, OUTPUT); pinMode(M3_PWM, OUTPUT);
  pinMode(M4_DIR, OUTPUT); pinMode(M4_PWM, OUTPUT);

  digitalWrite(M1_DIR, LOW); digitalWrite(M1_PWM, LOW);
  digitalWrite(M2_DIR, LOW); digitalWrite(M2_PWM, LOW);
  digitalWrite(M3_DIR, LOW); digitalWrite(M3_PWM, LOW);
  digitalWrite(M4_DIR, LOW); digitalWrite(M4_PWM, LOW);

  // Set PWM frequency to ~15 kHz (DMC60 compatible)
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;  // Pins 9, 10
  TCCR2B = (TCCR2B & 0b11111000) | 0x01;  // Pins 3, 11
  TCCR3B = (TCCR3B & 0b11111000) | 0x01;  // Pins 2, 5
  TCCR4B = (TCCR4B & 0b11111000) | 0x01;  // Pins 6, 7, 8
}

// === MOVE BOT (Basic Skid-Steering Logic for DMC60) ===
void move_bot() {
  // Calculate target speeds for left and right sides
  motor_1_speed = bot_speed - bot_direction;  // Left side target
  motor_2_speed = bot_speed + bot_direction;  // Right side target

  // Constrain speeds to PWM range (-255 to 255)
  motor_1_speed = constrain(motor_1_speed, -255, 255);
  motor_2_speed = constrain(motor_2_speed, -255, 255);

  // Apply to all motors (no torque distribution)
  int m1_target = motor_1_speed;  // Left-front
  int m3_target = motor_1_speed;  // Left-rear
  int m2_target = motor_2_speed;  // Right-front
  int m4_target = motor_2_speed;  // Right-rear

  // Apply direction and PWM to DMC60
  apply_pwm(M1_DIR, M1_PWM, m1_target);  // Left-front
  apply_pwm(M3_DIR, M3_PWM, m3_target);  // Left-rear
  apply_pwm(M2_DIR, M2_PWM, m2_target);  // Right-front
  apply_pwm(M4_DIR, M4_PWM, m4_target);  // Right-rear
}

// === APPLY PWM FOR DMC60 ===
void apply_pwm(int dir_pin, int pwm_pin, int target) {
  if (abs(target) > 12) {  // Dead zone
    digitalWrite(dir_pin, target > 0 ? HIGH : LOW);  // Set direction
    analogWrite(pwm_pin, abs(target));  // Set speed (0-255)
  } else {
    analogWrite(pwm_pin, 0);  // Neutral
  }
}

// === DEBUG PRINT ===
void send_data(uint16_t* ch) {
  Serial.print("CH1: "); Serial.print(ch[0]);
  Serial.print(" | CH2: "); Serial.print(ch[1]);
  Serial.print(" | CH3: "); Serial.print(ch[2]);
  Serial.print(" | Speed: "); Serial.print(bot_speed);
  Serial.print(" | Dir: "); Serial.print(bot_direction);
  Serial.print(" | Left: "); Serial.print(motor_1_speed);
  Serial.print(" | Right: "); Serial.println(motor_2_speed);
}