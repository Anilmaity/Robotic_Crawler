#include <iBus.h>

#define MAX_CHANNELS 10

iBus receiver(Serial4, MAX_CHANNELS);  // Serial2 pins in arduino giga

void ibus_setup() {
  receiver.begin();
}

void inspection_mode_setting() {
  if (inspection_mode == true) {
    if (ch[6] == 1000) {
      setting_mode = "WIFI";
    } else if (ch[6] == 1500) {
      setting_mode = "ANGLE";
    } else if (ch[6] == 2000) {
      setting_mode = "INSPECTION";
    }

    if (ch[7] == 1000) {
      if (setting_mode == "WIFI") {
        inspection_request_mode = "CONNECT";
      } else if (setting_mode == "ANGLE") {
        inspection_request_mode = "RESET PITCH";
      } else if (setting_mode == "INSPECTION") {
        inspection_request_mode = "NEW INSPEC";
      }
    }
 
    else if (ch[7] == 1500) {
      if (setting_mode == "WIFI") {
        inspection_request_mode = "ON";
      } else if (setting_mode == "ANGLE") {
        inspection_request_mode = "RESET YAW";
      } else if (setting_mode == "INSPECTION") {
        inspection_request_mode = "END Inspec";
      }
    }

    else if (ch[7] == 2000) {
      if (setting_mode == "WIFI") {
        inspection_request_mode = "OFF";
      } else if (setting_mode == "ANGLE") {
        inspection_request_mode = "RESET ENCODER";
      } else if (setting_mode == "INSPECTION") {
        inspection_request_mode = "RESET Inspec";
      }    }

    if (ch[9] == 2000) {
      if (setting_mode == "WIFI" && inspection_request_mode == "CONNECT") {connectToWiFi(); }
      else if (setting_mode == "WIFI" && inspection_request_mode == "ON") {turn_off_wifi_update = false; text_ok();}
      else if (setting_mode == "WIFI" && inspection_request_mode == "OFF") {turn_off_wifi_update = true; text_ok();}
      else if (setting_mode == "ANGLE" && inspection_request_mode == "RESET PITCH") {target_pitch_angle = pitch; text_ok();}
      else if (setting_mode == "ANGLE" && inspection_request_mode == "RESET ENCODER") {target_yaw_angle = yaw; text_ok();}
      else if (setting_mode == "ANGLE" && inspection_request_mode == "RESET ENCODER") {distance_travel =0; text_ok();}
      else if (setting_mode == "INSPECTION" && inspection_request_mode == "NEW INSPEC") {Serial.print(inspection_request_mode); text_ok();}
      else if (setting_mode == "INSPECTION" && inspection_request_mode == "END INSPEC") {Serial.print(inspection_request_mode); text_ok();}
      else if (setting_mode == "INSPECTION" && inspection_request_mode == "RESET INSPEC") {Serial.print(inspection_request_mode); text_ok();}

  }
}
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
      
      } // if (ch[8] == 2000 && wifi_connected == false) {
    //   connectToWiFi();  // 912
    //   ch[8] = 1500;
    // }
  }

  // if (ch[8] > 1900 && inspection_mode != true) {
  //   inspection_mode = true;  // 912
  // } else if (ch[8] < 1100 && inspection_mode != false) {
  //   inspection_mode = false;  // 912
  // }



  if (rc_connected == true && inspection_mode == false) {

    if (ch[5] >= 1200) {
      if (ch[3] <= 2000 && ch[3] >= 1000) {
        bot_speed = map(ch[3], 1000, 2000, 500, -500);
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

      if (ch[7] <= 2000 && ch[7] >= 1000) {
        if (ch[7] == 1000) {

          bot_direction = 0;
          no_360 = false;  // 912
                           // 912
        } else if (ch[7] == 1500) {
          no_360 = true;  // 912
          auto_pitch = false;
          auto_yaw = false;

        } else if (ch[7] == 2000) {
          bot_direction = bot_direction;  // 912
          no_360 = false;
          auto_pitch = false;
          auto_yaw = false;


          // 912
        }
      }


      if (ch[9] == 2000) {
        encoder_value = 0;  // 912
      }

      if (abs(bot_direction) + abs(bot_speed) > 5) {
        bot_mode = "RUNNING";
      } else {
        bot_mode = "RUNNING";
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
    bot_mode = "RC_ERROR";
    // Call blinking with red color (255, 0, 0)
  } else {
    inspection_mode_setting();
  }
}
