

void rc_loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // read one line
    command.trim();                                 // remove whitespace

    if (command == "PING") {
      Serial.println("OK");
      return;  // stop here, do not parse as motor command
    }


    // Check format
    if (command.startsWith("M-")) {
      int firstDash = command.indexOf('-');
      int secondDash = command.indexOf('-', firstDash + 1);

      if (secondDash > 0) {
        String motorStr = command.substring(firstDash + 1, secondDash);
        String speedStr = command.substring(secondDash + 1);

        int speed = speedStr.toInt();

        if (speed < -100 || speed > 100) {
          Serial.println("Error: Speed out of range (-100 to 100)");
          return;
        }

        if (motorStr == "A") {
          uart_bot_speed = speed;
          Serial.println("OK");


        } else if (motorStr == "D") {

          uart_bot_direction = speed;
          Serial.println("OK");

        }

        else {
          int motor = motorStr.toInt();

          if (motor >= 0 && motor < maxMotors) {

            if (motor == 1) {
              uart_m1_speed = speed;
            } else if (motor == 2) {
              uart_m2_speed = speed;

            } else if (motor == 3) {
              uart_m3_speed = speed;

            } else if (motor == 4) {
              uart_m4_speed = speed;
            }

          } else {
            Serial.println("Error: Motor number out of range");
          }
        }
      } else {
        Serial.println("Error: Invalid command format");
      }
    } else {
      Serial.println("Error: Command must start with M-");
    }
  }
}
