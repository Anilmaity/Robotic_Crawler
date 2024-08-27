#include <Wire.h>
#include <JY901.h>

int brake_pin[2] = { 4,3};  // pulse, dir , en
int brake_dir_pin[2] = { 5,2};  // pulse, dir , en
long int right_motor_step_count = 0;
long int left_motor_step_count = 0;

float target_angle = 0; 
float error_direction = 0;

int brake = 0;

int right_stepper_pin[3] = { 29, 25, 50 };  // pulse, dir , en
int left_stepper_pin[3] = { 39, 35, 53 };
long int imu_start;

float roll = 0;
float pitch = 0;
float yaw = 0;
int m1 = 0;
int m2 = 0;

int motor1_speed =0;
int motor2_speed =0;

bool auto_yaw = false;


double i_error = 0;
double previous_error = 0;


long int loopstart = 0;
long int loop_time = 0;
int channel_data[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


int bot_speed = 0;
int bot_direction = 0;

void setup() {
  // put your setp code here, to run once:
  Serial.begin(115200);
  Serial1.begin(9600);
  pinMode(13, OUTPUT);  
  digitalWrite(13, LOW); 
  
  ibus_setup();
  brakesetup();
  stepper_setup();

  imu_start = millis();
}

void loop() {
  // loopstart = micros();
  ibus_loop();
  braking();
  move_bot();

  loop_time = micros() - loopstart;

  if (millis() - imu_start > 10) {
    imu_start = millis();
   imu();
  }

    Serial.print(" ");
    Serial.print(bot_speed);
    Serial.print(" ");
    Serial.print(bot_direction);
    Serial.print(" ");
    Serial.print(motor1_speed);
    Serial.print(" ");
    Serial.print(motor2_speed);
    Serial.print(" ");

    Serial.print(" ");
    Serial.print(roll);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.print(yaw);
    Serial.print(" ");
    Serial.print(target_angle);
    Serial.print(" Mag: ");Serial.print(JY901.stcMag.h[0]);Serial.print(" ");Serial.print(JY901.stcMag.h[1]);Serial.print(" ");Serial.print(JY901.stcMag.h[2]);

    
    Serial.println(" ");




}

void imu() {
  // Serial.print("Angle:");
  // Serial.print((float)JY901.stcAngle.Angle[0] / 32768 * 180);
  // Serial.print(" ");
  // Serial.print((float)JY901.stcAngle.Angle[1] / 32768 * 180);
  // Serial.print(" ");
  // Serial.println((float)JY901.stcAngle.Angle[2] / 32768 * 180);
  roll = (float)JY901.stcAngle.Angle[0] / 32768 * 180;
  pitch = (float)JY901.stcAngle.Angle[1] / 32768 * 180;
  yaw = (float)JY901.stcAngle.Angle[2] / 32768 * 180;

  while (Serial1.available()) {
    JY901.CopeSerialData(Serial1.read());  //Call JY901 data cope function
  }
}
