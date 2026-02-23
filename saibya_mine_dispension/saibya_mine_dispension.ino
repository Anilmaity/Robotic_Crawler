#include "sbus.h"

#include <TinyGPS++.h>



#include <MAVLink.h>

TinyGPSPlus gps;


// ---------- BAUD RATES ----------
#define GPS_BAUD    38400
#define TELE_BAUD   250000
#define DEBUG_BAUD  115200


// ================= SBUS =================
bfs::SbusRx sbus_rx(&Serial1);
bfs::SbusData sbus_data;

unsigned long last_signal_time = 0;

// Map SBUS (172–1811) to PWM (1000–2000)
int sbusToPwm(int v) {
  v = constrain(v, 172, 1811);
  return map(v, 172, 1811, 1000, 2000);
}

// ================= MOTOR PINS =================
int M1_PWM = 2;  // Left-front
int M1_DIR = 3;
int M2_PWM = 5;  // Right-front
int M2_DIR = 4;
int M3_PWM = 6;  // Left-rear
int M3_DIR = 7;
int M4_PWM = 8;  // Right-rear
int M4_DIR = 9;

// Motor inversion flags (set true if motor spins backward physically)
bool M1_INV = false;
bool M2_INV = false;
bool M3_INV = true;
bool M4_INV = true;

// ================= CONTROL =================
float bot_speed = 0;      // -255 to 255
float bot_direction = 0;  // -255 to 255
float motor_1_speed = 0;  // Left side
float motor_2_speed = 0;  // Right side
float last_bot_speed = 0;
float deacceleration_rate = 1;
float max_speed = 255;

bool human_detected = false;
int human=0;
long int rad_last_debug = 0;
String serial3Line = "";

long int lidar_detect_time = 0;

// -------------------- DATA values --------------------
int v1 = 0, v2 = 0, v3 = 0, v4 = 0;


//

bool rc_connected = false;
// ================= SETUP =================
void setup() {
  Serial.begin(115200);
    // Serial.begin(DEBUG_BAUD);

  sbus_rx.Begin();
  motor_setup();
  gps_setup();
  Serial3.begin(TELE_BAUD);  // TELEMETRY → GCS
  Serial3.println("DATA:0 0 0 0");

  // reciever_setup();
  Serial.println("SBUS skid-steer controller started");
    // rad_setup();

}



// -------------------- Serial2 handler --------------------
void handleSerial() {
  while (Serial3.available()) {
    char c = Serial3.read();


    // Line buffering
    if (c == '\n') {
      processLine(serial3Line);
      serial3Line = "";
    } else if (c != '\r') {
      serial3Line += c;
    }
  }
}

// -------------------- Line processor --------------------
void processLine(const String& line) {
  if (line.startsWith("DATA:")) {
    sscanf(line.c_str(), "DATA:%d %d %d %d", &v1, &v2, &v3, &v4);

    // Serial.print("Decoded DATA: ");
    // Serial.print(v1);
    // Serial.print(", ");
    // Serial.print(v2);
    // Serial.print(", ");
    // Serial.print(v3);
    // Serial.print(", ");
    // Serial.println(v4);
  }
}

// ================= LOOP =================
void loop() {
  static unsigned long last_motor_update = 0;
  static unsigned long last_debug = 0;

  gps_loop();
  reciever_loop();
  handleSerial();


  rc_connected = (millis() - last_signal_time < 500);

  sbus_loop();

  // -------- MOTOR UPDATE (1 kHz) --------
  if (micros() - last_motor_update >= 1000) {
    last_motor_update = micros();
       move_bot();


    // if (sbusToPwm(sbus_data.ch[6]) < 1500) {
    //   move_bot();
    // } else if (sbusToPwm(sbus_data.ch[6]) > 1500) {

    //   if (v2 == 1) {
    //     max_speed = 100;
    //   } else {
    //     max_speed = 255;
    //   }

    //   if (v3 == 1) {


    //     if ((millis() - lidar_detect_time) > 50)
    //     {
    //     bot_speed = 0;
    //     bot_direction = 0;
    //     last_bot_speed = 0;
    //     }

    //     move_bot();


    //   } else {

    //     lidar_detect_time = millis();

    //     move_bot();
    //   }

     }
  

  // -------- DEBUG --------
  if (millis() - last_debug > 100) {
    last_debug = millis();
     send_debug();
    // rad_loop();
    if(rc_connected){
    send_data();

    }
    else{

    Serial3.println("DATA:0 0 0 0");

    }
  }

  //   if (millis() - rad_last_debug > 500) {
  //   rad_last_debug = millis();
  //   // send_debug();
  //   // rad_loop();

  //   // send_data();
  // }

}



// ================= MOTOR SETUP =================
void motor_setup() {
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M3_DIR, OUTPUT);
  pinMode(M3_PWM, OUTPUT);
  pinMode(M4_DIR, OUTPUT);
  pinMode(M4_PWM, OUTPUT);
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
  analogWrite(M3_PWM, 0);
  analogWrite(M4_PWM, 0);


  // Optional: ESP32 PWM frequency setup if needed
  // Optional: Arduino Mega PWM frequency for DMC60
  TCCR1B = (TCCR1B & 0b11111000) | 0x01;
  TCCR2B = (TCCR2B & 0b11111000) | 0x01;
  TCCR3B = (TCCR3B & 0b11111000) | 0x01;
  TCCR4B = (TCCR4B & 0b11111000) | 0x01;
}

// ================= MOVE BOT =================
void move_bot() {
  // Skid-steer differential

  if (abs(last_bot_speed) >= abs(bot_speed)) {
    if (last_bot_speed > 1) {

      bot_speed = last_bot_speed - deacceleration_rate;
      last_bot_speed = bot_speed;
    } else if ((last_bot_speed < -1)) {
      bot_speed = last_bot_speed + deacceleration_rate;
      last_bot_speed = bot_speed;
    }

  } 
  if(abs(last_bot_speed) <= abs(bot_speed)){
          last_bot_speed = bot_speed;

  }
  
  // else {
  //   if (abs(last_bot_speed) < 10 || abs(last_bot_speed) <= abs(bot_speed)) {
  //     last_bot_speed = bot_speed;

  //     bot_speed = bot_speed;
  //   }
  // }

  motor_1_speed = constrain(bot_speed - bot_direction, -max_speed, max_speed);  // Left
  motor_2_speed = constrain(bot_speed + bot_direction, -max_speed, max_speed);  // Right

  // Apply speeds to all motors with inversion flags
  apply_pwm(M1_DIR, M1_PWM, motor_1_speed, M1_INV);  // Left-front
  apply_pwm(M3_DIR, M3_PWM, motor_1_speed, M3_INV);  // Left-rear
  apply_pwm(M2_DIR, M2_PWM, motor_2_speed, M2_INV);  // Right-front
  apply_pwm(M4_DIR, M4_PWM, motor_2_speed, M4_INV);  // Right-rear
}

// ================= APPLY PWM =================
void apply_pwm(int dir_pin, int pwm_pin, int target, bool invert) {
  if (abs(target) > 12) {  // dead zone
    bool dir = target > 0;
    if (invert) dir = !dir;
    digitalWrite(dir_pin, dir ? HIGH : LOW);
    analogWrite(pwm_pin, abs(target));
  } else {
    analogWrite(pwm_pin, 0);
  }
}

// ================= DEBUG =================
void send_debug() {
  Serial.print("Thr: ");
  Serial.print(bot_speed);
  Serial.print(" last Thr: ");
  Serial.print(last_bot_speed);
  Serial.print(" | Str: ");
  Serial.print(bot_direction);
  Serial.print(" | Left: ");
  Serial.print(motor_1_speed);
  Serial.print(" | Right: ");
  Serial.print(motor_2_speed);

  Serial.print(" | DATA:");
  Serial.print(v1);
  Serial.print(",");
  Serial.print(v2);
  Serial.print(",");
  Serial.print(v3);
  Serial.print(",");
  Serial.print(v4);

  Serial.print(" , ");
  Serial.println(sbus_data.ch[0]);
}
