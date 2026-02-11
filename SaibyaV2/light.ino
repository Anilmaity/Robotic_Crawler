void light_setup(){

    pinMode(LIGHT_LED, OUTPUT);

}

void updateLightStatus(){

  if(light_on)
  {
    digitalWrite(LIGHT_LED, LOW);
  }
  else
  {
    digitalWrite(LIGHT_LED, HIGH);
  }

}