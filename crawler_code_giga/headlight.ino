void light() {
  pinMode(relay_pin, OUTPUT);
}

void light_operate() {
  if (relay_value = 1) {
    digitalWrite(relay_pin, HIGH);
  } else {
    digitalWrite(relay_pin, LOW);
  }
}