void light() {
  pinMode(relay_pin, OUTPUT);
  pinMode(relay_pin1, OUTPUT);

}

void light_operate() {
  if (relay_value == 1) {
    digitalWrite(relay_pin, LOW);
      digitalWrite(relay_pin1, LOW);
} else {
    digitalWrite(relay_pin, HIGH);
      digitalWrite(relay_pin1, HIGH);
}
}