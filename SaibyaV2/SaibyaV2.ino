#include <AlfredoCRSF.h>
#include <HardwareSerial.h>

#define PIN_RX 10
#define PIN_TX 9
#define PIN_LED 15
#define LIGHT_LED 13


// Set up a new Serial object
HardwareSerial crsfSerial(2);
AlfredoCRSF crsf;



int Reverse_pin = 3;
int Brake_pin = 4;



bool rc_connected = true;
long int Current_Speed;
long int loopstart = 0;
long int loop_time = 0;
long int motor_driver_start_time = 0;
long int Sterring_input = 0;

unsigned long int a, b, c;
volatile int  ch[16];




// Variables for brake
int Brake = 0;
int initial_brake = 0;
bool brake_time_modified = false;
long int brake_time = 0;
long int brake_start_time=0;
int extented_brake = 32;
int brake_point = 35;


int brake_pwm_pin = 6;

#define PWM_CHANNEL 0
#define PWM_FREQUENCY 75000   // 25 kHz
#define PWM_RESOLUTION 8      // 8-bit (0–255)



int brake_dir_pin = 5;

bool braked = false; 

int max_brake = 19;


// sterring_value
int S_DIR = 7;
int S_PWM = 8;
String binStr = "";


long int sterring_value =180;
long int error_sterring = 0;
int sensorValue = -100;
int p_sterring = 50;


float default_acceleration = 0.3;
float default_deacceleration = 1;

float high_acceleration = 0.9;
float high_deacceleration = 3;

float very_high_acceleration = 2;
float very_high_deacceleration = 6;



// throttle
float speed_increase_rate_forward = 0.3;   // if you want to increase bot acceleration in forward direction
float speed_increase_rate_backward = 0.3; // if you want to increase bot acceleration in reverse direction
float speed_decrease_rate = 1;          // if you want to decrease bot acceleration in both direction

int initial_throttle = 115;
int initial_throttle_backward = 115;
int max_limit = 202; // max speed limit
int max_high_speed = 255;
int max_low_speed = 202;
int throttle_pin = 2;
int throttle = 0;
double input_throttle = 0;


// light
bool light_on = false;


void setup()
{
  Serial.begin(1000000);
  Serial.println("COM Serial initialized");
  rc_setup();
  sterring_setup();
  throttle_setup();
  light_setup();

}






void send_data() {



  Serial.print(ch[1]); // 1500 1500 1500 1500 1500 0 0 85 548 0 0 1
  Serial.print(" ");
  Serial.print(ch[2]);
  Serial.print(" ");
  Serial.print(ch[3]);
  Serial.print(" ");
  Serial.print(ch[4]);
  Serial.print(" ");
  Serial.print(ch[5]);
  Serial.print(" ");


  Serial.print(" ");
  Serial.print(throttle);
  Serial.print(" ");
  Serial.print(input_throttle);
  Serial.print(" ");

  Serial.print(Brake);
  Serial.print(" ");
  Serial.print(brake_time);
  Serial.print(" ");


  Serial.print(sterring_value);
  Serial.print(" ");
  Serial.print(error_sterring);
  Serial.print(" ");
  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.print(loop_time);
  Serial.println(" ");
}


void loop()
{
  loopstart = millis();
  rc_loop();
  evaluteinputs();
  send_data();
  throttling();
  delay(5); // delay 1 millisecond
  updateLightStatus();
  loop_time = millis() - loopstart;


}



