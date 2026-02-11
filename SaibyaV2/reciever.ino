int highest_sterring_value = 210;
int default_sterring_value = 180;
int lowest_sterring_value = 150;

void rc_setup()
{
  
  crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1, PIN_RX, PIN_TX);
  if (!crsfSerial) while (1) Serial.println("Invalid crsfSerial configuration");

  crsf.begin(crsfSerial);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
}

void rc_loop()
{
    // Must call crsf.update() in loop() to process data
    crsf.update();
    for (int ChannelNum = 1; ChannelNum <= 10; ChannelNum++)
    {
      // Serial.print(crsf.getChannel(ChannelNum));
      // Serial.print(", ");
      ch[ChannelNum] = crsf.getChannel(ChannelNum);
    }
        // Serial.println(" ");

      updateLinkStatusLed();

}




void updateLinkStatusLed()
{
  if(crsf.isLinkUp())
  {
    digitalWrite(PIN_LED, LOW);
  }
  else
  {
    digitalWrite(PIN_LED, HIGH);
    // Perform the failsafe action
  }
}






void evaluteinputs() {

  if (ch[5] >= 1600) {
    if (ch[2] <= 2100 && ch[2] >= 1520) {
      throttle = 0.5 * throttle + 0.5 * map(ch[2], 1500, 2000, initial_throttle, max_limit);
    } else if (ch[2] <= 1480 && ch[2] >= 900) {
      throttle = 0.5 * throttle + 0.5 * map(ch[2], 1000, 1500, -max_limit, -initial_throttle_backward );
    } else {
      throttle = 0;
    }


    if (ch[1] <= 2100 && ch[1] >= 1510) {
      sterring_value = map(ch[1], 1500, 2000, default_sterring_value, highest_sterring_value); // 912
    } else if (ch[1] <= 1490 && ch[1] >= 900) {
      sterring_value = map(ch[1], 1000, 1500, lowest_sterring_value, default_sterring_value); // 548 // 227
    } else {
      sterring_value = default_sterring_value;

    }


    if (ch[3] <= 2100 && ch[3] >= 900) {
      Brake = map(ch[3], 1000, 1900, initial_brake, max_brake); // max brake angle
    } 
    else{
      Brake = initial_brake;
    }

   if (ch[6] <= 2100 && ch[6] >= 900) {

    if(ch[6] > 1600){

      max_limit = max_high_speed;
    }
    else{

      max_limit = max_low_speed;
    }


       } 


    if (ch[7] <= 2100 && ch[7] >= 900) {

    if(ch[7] > 1600){

      light_on = true;
    }
    else{

      light_on  = false;
    }

    if (ch[8] <= 2100 && ch[8] >= 900) {

    if(ch[8] < 1400 && ch[8] > 900){

      speed_increase_rate_forward = default_acceleration;  
      speed_increase_rate_backward = default_acceleration; 
      speed_decrease_rate = default_deacceleration; 
    }
    else if(ch[8] > 1400 && ch[8] < 1600){

      speed_increase_rate_forward = high_acceleration;  
      speed_increase_rate_backward = high_acceleration; 
      speed_decrease_rate = high_deacceleration; 
      
          }
        
      else{


      speed_increase_rate_forward = very_high_acceleration;  
      speed_increase_rate_backward = very_high_acceleration; 
      speed_decrease_rate = very_high_deacceleration; 

      }


       } 






       } 

    



  } else {

    throttle = 0;
  }
}