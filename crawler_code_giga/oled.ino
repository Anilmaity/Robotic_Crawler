
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

void oled_setup() {
  Wire1.begin();
  oled.init(Wire1);
  oled.clearDisplay();
}

void connecting_to_wifi() {
  oled.setTextXY(2, 1);
  oled.putString("CONNECTING TO");
  oled.setTextXY(4, 2);
  oled.putString("WIFI");
}

void connected() {
  oled.clearDisplay();
  oled.setTextXY(2, 1);
  oled.putString("CONNECTED");
}

void not_connected() {
  oled.clearDisplay();
  oled.setTextXY(2, 1);
  oled.putString("FAILED TO");
  oled.setTextXY(4, 1);
  oled.putString("CONNECT");
}

void default_text() {
  oled.clearDisplay();
  oled.setTextXY(2, 1);
  oled.putString("ARNOBOT");
  oled.setTextXY(4, 1);
  oled.putString("Inspectobot,");
}

void inspection_text() {
  oled.clearDisplay();
  oled.setTextXY(2, 1);
  oled.putString("Inspec Mode");
}
void inspection_text_update() {
  oled.setTextXY(4, 1);
  oled.putString(inspection_request_mode);
}
void text_ok() {
  oled.clearDisplay();
  oled.setTextXY(2, 1);
  oled.putString("OK");
  oled.setTextXY(4, 1);
  oled.putString("     ");
}
void text_display(String value) {
  oled.clearDisplay();
  oled.setTextXY(2, 1);
  oled.putString(value);
}
void clear_display() {
  oled.clearDisplay();
}

String format_value(float value) {
    int intValue = int(value);  // Convert float to int

    // Handle negative zero case explicitly
    if (intValue == 0 && value < 0) {
        intValue = 0;  // Ensure -0 is displayed as 0
    }

    // Create a string to store the formatted value
    String formattedValue;

    // Positive or zero case
    if (intValue >= 0) {
        if (intValue < 10) {
            // Pad with two spaces if it's a single digit positive number
            formattedValue = "  " + String(intValue);
        } else {
            // Pad with one space if it's a two-digit positive number
            formattedValue = " " + String(intValue);
        }
    } else {
        // Negative case: the length is naturally 3 when it's negative (-10)
        if (intValue > -10) {
            // Pad with two spaces if it's a single digit positive number
            formattedValue = " " + String(intValue);
        } else {
            // Pad with one space if it's a two-digit positive number
          formattedValue = String(intValue);
        }
    }

    return formattedValue;
}

void update_imu() {
  oled.setTextXY(6, 1);
  oled.putString(format_value(roll));

  oled.setTextXY(6, 6);
  oled.putString(format_value(pitch));


   oled.setTextXY(6, 11);
  oled.putString(format_value(yaw));
}