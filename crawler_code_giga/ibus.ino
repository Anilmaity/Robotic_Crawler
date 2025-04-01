


void serial_setup() {
  Serial4.begin(115200);
}

void data_loop() {
  static String receivedData = "";  // Store received characters

  while (Serial4.available()) {
    char inChar = Serial4.read();

    if (inChar == '\n') {  // End of message
      extractData(receivedData);  // Extract and store numbers
      receivedData = "";  // Clear buffer for next message
    } else {
      receivedData += inChar;  // Append character to string
    }
  }

  evaluate();
}

void extractData(String data) {
  int index = 1;
  char buffer[10];  // Temporary buffer for number conversion
  int bufferIndex = 0;

  for (int i = 0; i < data.length(); i++) {
    if (data[i] == ' ' || i == data.length() - 1) {
      if (bufferIndex > 0) {
        buffer[bufferIndex] = '\0';  // Null-terminate string
        if (index < MAX_CHANNELS) {
          ch[index++ ] = atoi(buffer);  // Convert string to int
        }
        bufferIndex = 0;  // Reset buffer
      }
    } else {
      if (bufferIndex < 5) {  // Ensure buffer does not overflow
        buffer[bufferIndex++] = data[i];
      }
    }
  }

}

  // Debug: Print extracted values
  // Serial.print("Extracted: ");
void evaluate() {

  for (byte i = 1; i <= MAX_CHANNELS; i++) {  // get channel values starting from 1


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


      if (ch[1] <= 2000 && ch[1] >= 1000 && (ch[1] <= 1495 || ch[1] >= 1505)) {
        bot_direction = map(ch[1], 1000, 2000, -1000, 1000);  // 912
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
  }
}




