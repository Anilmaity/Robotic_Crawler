int ENC_A =51;
int ENC_B =53;



void encoder_setup() {
  pinMode(ENC_A, INPUT_PULLUP); 
  pinMode(ENC_B, INPUT_PULLUP);


  attachInterrupt(digitalPinToInterrupt(ENC_A), decode_rotation_A, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_B), decode_rotation_B, RISING);
  // enabling interrupt at pin 2
}

void decode_rotation_A() {
  int A = digitalRead(ENC_A);
  int B = digitalRead(ENC_B);


  if (A == 1 && B == 0) {
    position_A -= 1;

  }
  else if (A == 1 && B == 1) {
   position_A += 1;

  }
  position = int((position_A + position_B) / 2);


}

void decode_rotation_B() {
  int A = digitalRead(ENC_A);
  int  B = digitalRead(ENC_B);


  if (A == 0 && B == 1) {
    position_B += 1;

  }
  else if (A == 1 && B == 1) {
    position_B -= 1;

  }
  position = int((position_A + position_B) / 2);


}