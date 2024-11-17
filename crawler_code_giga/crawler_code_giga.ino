// Librarys and includes
#include <ArduinoWebsockets.h>
#include <Wire.h>
#include <JY901.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>

// Variables for Communication
int channel_data[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int ch[15];

// Variables for Brake Contrl
// int brake_pin[2] = { 4, 3 };      // pulse, dir , en
// int brake_dir_pin[2] = { 5, 2 };  // pulse, dir , en
// int brake = 0;

// Variables for RGB Control
long int rgb_time = 0;
bool lights_on = false;

// Variables for Inspection Mode
bool inspection_mode = false;

// Variables for Auto Yaw
float target_angle = 0;
float error_direction = 0;

// Variables for Movement log
long int right_motor_step_count = 0;
long int left_motor_step_count = 0;
long int total_steps = 0;
bool no_360 = true;

// Variables for STEPPER PINS
int right_stepper_pin[3] = { 29, 25, 50 };  // pulse, dir , en
int left_stepper_pin[3] = { 39, 35, 52 };

// Variables for Bot Control
int m1 = 0;
int m2 = 0;
int speed_setting = 700;
int motor1_speed = 0;
int motor2_speed = 0;
int bot_speed = 0;
int bot_direction = 0;



// Variables for IMU
float roll = 0;
float pitch = 0;
float yaw = 0;

// Variables for  Auto Position
bool auto_yaw = false;
double i_error = 0;
double previous_error = 0;

// Variables for Bot State
bool rc_connected = false;
String inspection_request_mode = "New Inspection";
String bot_mode = "OFF";
String previous_bot_mode = "IDLE";
bool wifi_connected = true;
long rssi = 0;  // Get the RSSI value


// Variable for Current Sensor
float current_value = 0;

// Variable for Turning off Features
bool turn_off_wifi_update = false;
bool turn_off_imu_update = false;
bool turn_off_oled_update = false;
bool turn_off_current_update = false;
bool turn_off_stepper_update = false;
bool turn_off_encoder_update = false;
bool turn_off_rgb_lights = false;
bool turn_off_serial_logs = false;

// Variable for Encoder
volatile float distance_travel = 0;
volatile long int encoder_value = 0;

// Variable for Timers
long int oled_update = 0;
long int imu_start;
long int update_data;
long int loopstart = 0;
long int loop_time = 0;

void setup() {
  leds_setup();
  //red();
  oled_setup();
  // put your setp code here, to run once:
  Serial.begin(921600);
  Serial2.begin(9600);
  encoder_setup();
  current_setup();
  ibus_setup();
  stepper_setup();
  imu_start = millis();
  update_data = millis();
  connectToWiFi();
  //white();
}



void loop() {
  loop_time = millis() - loopstart;
  loopstart = millis();
  move_bot();

  if (millis() - imu_start > 50) {
    if (turn_off_imu_update == false) { imu();}
    imu_start = millis();
  }

  if (inspection_mode == true && (millis() - oled_update) > 100) {
      inspection_text_update();
      oled_update = millis();
    }

  //send_data();

  if (turn_off_rgb_lights == false) { led_control();}

  if (millis() - update_data > 3000) {
    if (turn_off_serial_logs == false) { serial_logs();}
    if (turn_off_wifi_update == false) { updateData();}
    if (turn_off_current_update == false) { current_reading();}

    Serial.println(millis() - update_data);
    update_data = millis();

  }
}

