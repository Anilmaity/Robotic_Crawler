

void rc_read() {
  if (Serial4.available() > 0) {
    String command = Serial4.readStringUntil('\n'); // read one line
    command.trim(); // remove whitespace

    // Check format
    if (command.startsWith("M-")) {
      int firstDash = command.indexOf('-');
      int secondDash = command.indexOf('-', firstDash + 1);

      if (secondDash > 0) {
        String motorStr = command.substring(firstDash + 1, secondDash);
        String speedStr = command.substring(secondDash + 1);

        int speed = speedStr.toInt();

        if (speed < -255 || speed > 255) {
          Serial.println("Error: Speed out of range (-255 to 255)");
          return;
        }

        if (motorStr == "A") {
          // All motors
          Serial.print("All motors set to speed: ");
          Serial.println(speed);
          for (int i = 0; i < maxMotors; i++) {
            Serial.print("Motor "); Serial.print(i);
            Serial.print(" -> Speed: "); Serial.println(speed);
          }
        } else {
          int motor = motorStr.toInt();
          if (motor >= 0 && motor < maxMotors) {
            Serial.print("Motor "); Serial.print(motor);
            Serial.print(" -> Speed: "); Serial.println(speed);
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
