#include <Wire.h>
#include <JY901.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>
long int rgb_time = 0;
int ch[15];
int brake_pin[2] = { 4, 3 };      // pulse, dir , en
int brake_dir_pin[2] = { 5, 2 };  // pulse, dir , en
long int right_motor_step_count = 0;
long int left_motor_step_count = 0;
long int total_steps = 0;
float target_angle = 0;
float error_direction = 0;
bool no_360 = true;
int brake = 0;
bool white_off = true;
float position = 0;
int position_A = 0;
int position_B = 0;

int right_stepper_pin[3] = { 29, 25, 50 };  // pulse, dir , en
int left_stepper_pin[3] = { 39, 35, 53 };
long int imu_start;
long int update_data;

float roll = 0;
float pitch = 0;
float yaw = 0;
int m1 = 0;
int m2 = 0;

int motor1_speed = 0;
int motor2_speed = 0;

bool auto_yaw = false;


double i_error = 0;
double previous_error = 0;


long int loopstart = 0;
long int loop_time = 0;
int channel_data[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
bool rc_connected = false;

int bot_speed = 0;
int bot_direction = 0;


int speed_setting = 505;
long rssi = 0;  // Get the RSSI value

// current reading
float current_value= 0;


void setup() {
  leds_setup();
  red();
  oled_setup();
  // put your setp code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600);
  encoder_setup();
  current_setup();
  ibus_setup();
  //brakesetup();
  stepper_setup();
  imu_start = millis();
  update_data = millis();
  connectToWiFi();
}

void loop() {
  loopstart = millis();
  ibus_loop();
  move_bot();
  loop_time = millis() - loopstart;
  // test();
  if (millis() - imu_start > 50) {
    imu();
    imu_start = millis();
  }
  current_reading();
  send_data();

  if (millis() - update_data > 3000) {
    //white();
    send_data();
    update_data = millis();
    Serial.println("Sending");
    updateData();
    Serial.println(millis() - update_data);
    //off();
  }
}

void send_data() {
  Serial.print(" ");
  Serial.print(ch[1]);
  Serial.print(" ");
  Serial.print(ch[2]);
  Serial.print(" ");
  Serial.print(ch[3]);
  Serial.print(" ");
  Serial.print(ch[4]);
  Serial.print(" ");
  Serial.print(ch[5]);
  Serial.print(" ");
  Serial.print(ch[6]);
  Serial.print(" ");
  Serial.print(ch[7]);
  Serial.print(" ");
  Serial.print(ch[8]);
  Serial.print("   ");
  Serial.print(bot_speed);
  Serial.print(" ");
  Serial.print(bot_direction);
  Serial.print(" ");
  Serial.print(motor1_speed);
  Serial.print(" ");
  Serial.print(motor2_speed);

  Serial.print(" ");
  Serial.print(position);
  Serial.print(" ");
  Serial.print(loop_time);
  Serial.print(" ");


  // Serial.print(" ");
  // Serial.print(roll);
  // Serial.print(" ");
  // Serial.print(pitch);
  // Serial.print(" ");
  // Serial.print(yaw);
  // // Serial.print(" ");
  // // Serial.print(target_angle);
  // Serial.print(" Mag: ");
  // Serial.print(JY901.stcMag.h[0]);
  // Serial.print(" ");
  // Serial.print(JY901.stcMag.h[1]);
  // Serial.print(" ");
  // Serial.print(JY901.stcMag.h[2]);


  Serial.println();
}
