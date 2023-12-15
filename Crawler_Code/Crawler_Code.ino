long int loopstart = 0;
long int loop_time = 0;
int channel_data[10] = {0,0,0,0,0,0,0,0,0,0};

int right_motor_pin[2] = {3,2}; // DIR , PWM
int left_motor_pin[2] = {5,4};  // DIR , PWM

int bot_speed = 0;
int bot_direction = 0;

void setup() {
  // put your setp code here, to run once:
  Serial.begin(115200);
  Serial3.setTimeout(100);
  ibus_setup();


}

void loop(){
loopstart = millis();
ibus_loop();
move_bot();

loop_time = millis() - loopstart;
}


