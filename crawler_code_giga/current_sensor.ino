int InputPin = A0;

void current_setup() {
  pinMode(InputPin, INPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
}


void current_reading() {
  if (analogRead(InputPin) >= 775) {
    current_value = analogRead(InputPin) - 775;
  }else {
    current_value = 0;
  }
}