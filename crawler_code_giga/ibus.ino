#include <iBus.h>

#define MAX_CHANNELS 10

iBus receiver(Serial4, MAX_CHANNELS);  // Serial2 pins in arduino giga

void ibus_setup() {
  receiver.begin();
}



void ibus_loop() {
  receiver.process();
  for (byte i = 1; i <= MAX_CHANNELS; i++) {  // get channel values starting from 1
    int value = receiver.get(i);
    if (value >= 1000 && value <= 2000) {
      ch[i] = value;
    }

    if (ch[10] > 1000) {
      rc_connected = true;  // 912
    } else {
      rc_connected = false;
    }

    if (ch[8] <= 2000 && ch[8] >= 1000) {
        if(ch[8] ==1000) {relay_value = 0;}
        else{
          relay_value = 1;
        }
      
      } 
  }

  // if (ch[8] > 1900 && inspection_mode != true) {
  //   inspection_mode = true;  // 912
  // } else if (ch[8] < 1100 && inspection_mode != false) {
  //   inspection_mode = false;  // 912
  // }



  if (rc_connected == true && inspection_mode == false) {

    if (ch[5] >= 1200) {
      if (ch[3] <= 2000 && ch[3] >= 1000) {
        bot_speed = map(ch[3], 1000, 2000, 1000, -1000);
      } else {
        bot_speed = 0;
      }


      if (ch[1] <= 2000 && ch[1] >= 1000) {
        bot_direction = map(ch[1], 1000, 2000, -500, 500);  // 912
      } else {
        bot_direction = 0;  // 912
      }

      if (ch[6] == 1500) {
        auto_pitch = true;
        auto_yaw = false;

      } else if (ch[6] == 2000) {
        auto_yaw = true;
        auto_pitch = false;

      } else if (ch[6] == 2000) {
        auto_yaw = false;
        auto_pitch = false;
      }
      if (abs(bot_direction) + abs(bot_speed) > 5) {
        bot_mode = "ON";
      } else {
        bot_mode = "ON";
      }
      if (ch[7] <= 2000 && ch[7] >= 1000) {
        if (ch[7] == 1000) {
        bot_mode = "AT";

          bot_direction = 0;
          no_360 = false;  // 912
                           // 912
        } else if (ch[7] == 1500) {
          bot_mode = "N";
          no_360 = true;  // 912
          auto_pitch = false;
          auto_yaw = false;

        } else if (ch[7] == 2000) {
          bot_direction = bot_direction;  // 912
          no_360 = false;
          auto_pitch = false;
          auto_yaw = false;
          bot_mode = "360";


          // 912
        }
      }


      if (ch[9] == 2000) {
        encoder_value = 0;  // 912
      }




    } else {
      bot_mode = "OFF";
      bot_speed = 0;
      bot_direction = 0;
    }
  }

  else if (inspection_mode == false) {

    bot_speed = 0;
    bot_direction = 0;
    bot_mode = "RCER";
    // Call blinking with red color (255, 0, 0)
  } 
}
