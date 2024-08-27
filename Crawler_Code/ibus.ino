#include <IBusBM.h>


IBusBM IBus;  // IBus object

void ibus_setup() {

  //IBus.begin(Serial);    // iBUS connected to Serial0 - change to Serial1 or Serial2 port when required
  IBus.begin(Serial3);
  Serial.println("Start IBus2PWM");
}


void ibus_loop() {


  for (int i = 0; i <= 9; i++) {
    channel_data[i] = IBus.readChannel(i);  // get latest value for servo channel 1
    //Serial.print(channel_data[i]);
    //Serial.print(Serial3.available());
    //Serial.print(" ");
  }



  //------------------------- ON OFF --------------------
  if (channel_data[4] == 2000) {
    // Getting values form all channel


    // Serial.println();

    //-------------------------forward backward---------------------
    if (channel_data[2] <= 2000 && channel_data[2] >= 1000) {
      bot_speed = map(channel_data[2], 1000, 2000, 500, -500);
    } else {
      bot_speed = 0;
    }

    //-------------------------Direction---------------------
    if (channel_data[0] <= 2000 && channel_data[0] >= 1000) {
      bot_direction = map(channel_data[0], 1000, 2000, -500, 500);
    } else {
      bot_direction = 0;
    }

    if (channel_data[9] == 2000) {
      target_angle = yaw;
    }

    if (channel_data[5] == 2000) {
        error_direction = -int((target_angle - yaw) * 100);
        if (error_direction > 1000) {
          error_direction = 1000;
        } else if (error_direction < -1000) {
          error_direction = -1000;
        }
        else if(abs(error_direction) < 5){
          error_direction =0;
        }
      
      bot_direction = 0;


    } else {
      error_direction = 0;
    }
  }
  else{
    error_direction = 0;
    bot_direction =0;
    bot_speed = 0;
    

  }
}
