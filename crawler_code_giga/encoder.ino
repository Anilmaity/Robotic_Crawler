#define ENC_A  38  // Example pin number for encoder pin A (must be interrupt capable)
#define ENC_B  40  // Example pin number for encoder pin B

volatile int last_encA_state = LOW;

void encoder_setup() {
 pinMode(ENC_A, INPUT_PULLUP);  // Enable internal pull-up for pin A
  pinMode(ENC_B, INPUT_PULLUP);  // Enable internal pull-up for pin B
  // Attach interrupt to ENC_A pin for state change
  attachInterrupt(digitalPinToInterrupt(ENC_A), updateEncoder, CHANGE); 
 pinMode(ENC_A, INPUT_PULLUP);  // Enable internal pull-up for pin A
  pinMode(ENC_B, INPUT_PULLUP);  // Enable internal pull-up for pin B

}



void updateEncoder() {
  // Read the state of the encoder pins
  encoder_connect_time = millis();
  int encA_state = digitalRead(ENC_A);
  int encB_state = digitalRead(ENC_B);

  // Detect state change of ENC_A and determine the rotation direction
  if (encA_state != last_encA_state) {
    // If ENC_B state is different from ENC_A, the encoder is rotating clockwise
    if (digitalRead(ENC_B) != encA_state) {
      encoder_value++;
    } else {
      // If ENC_B state is the same as ENC_A, the encoder is rotating counterclockwise
      encoder_value--;
    }
    last_encA_state = encA_state;
    distance_travel = (encoder_value*0.2)/1200;
  }
}
