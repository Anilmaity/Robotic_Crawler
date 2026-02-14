#include <AlfredoCRSF.h>
#include "mbed.h"
#include <crsf_protocol.h>

// ================= CONFIG =================
#define MAX_CHANNELS 8


int maxMotors = 4;
int maxspeed = 255;
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


int uart_bot_speed = 0;
int uart_bot_direction = 0;
int uart_m1_speed = 0;
int uart_m2_speed = 0;
int uart_m3_speed = 0;
int uart_m4_speed = 0;
bool resp_rc = false;



String inputString = "";
bool stringComplete = false;


// ================= MBED PWM OBJECTS =================
mbed::PwmOut* pwm1;
mbed::PwmOut* pwm2;
mbed::PwmOut* pwm3;
mbed::PwmOut* pwm4;

// ================= SETUP =================
void setup() {
  Serial.begin(250000);
  Serial1.begin(250000);
  Serial4.begin(250000);
  
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
  // Motor update @ 1kHz
  if (micros() - last_motor_update >= 1000) {
    last_motor_update = micros();

    if(resp_rc){
      move_bot_rc();
    }
    else{
      move_bot_uart();
    }

    
  }

  // Debug
  // if (millis() - last_debug > 100) {
  //   last_debug = millis();
  //   send_data();
  // }

  resp_rc = rc_read();
  rc_loop();
  c_loop();


  
 
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
