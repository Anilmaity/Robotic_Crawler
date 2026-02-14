

void rc_read(){

  
  crsf.update();
  bool rc_connected = crsf.isLinkUp();

  if (rc_connected) {
    for (int i = 0; i < MAX_CHANNELS; i++) {
      channels[i] = crsf.getChannel(i + 1);
    }

    bool armed = (channels[4] > 1400);

    handleRelay(RELAY1_PIN, channels[5]);  // CH5 is index 4
    //handleRelay(RELAY2_PIN, channels[5]);  // CH5 is index 4


    if (armed) {

    int throttle_input = channels[1];
    int steer_input    = channels[3];

    // Map CRSF range (~1000–2000) to -255 to 255
    bot_speed     = map(throttle_input, 1000, 2000, -255, 255);
    bot_direction = map(steer_input,    1000, 2000, -255, 255);

    // Optional: small deadband around center
    if (abs(bot_speed) < 10) bot_speed = 0;
    if (abs(bot_direction) < 10) bot_direction = 0;

    skid = (channels[6] > 1400);





    } else {
      bot_speed = 0;
      bot_direction = 0;
    }
  } else {
    bot_speed = 0;
    bot_direction = 0;
    // digitalWrite(RELAY1_PIN, LOW);
    // digitalWrite(RELAY2_PIN, LOW);
  }



}