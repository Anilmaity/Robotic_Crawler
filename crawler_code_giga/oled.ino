
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
String oled_text = "NONE";
String previous_oled_text = "NONE";
String mode_text = "";
String previous_mode_text = "";

void oled_setup() {
  Wire.begin();
  oled.init(Wire);
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
  oled_text = "S=ON";
  if(rc_connected == false)  oled_text = "S=RCER";
  if(bot_mode == "OFF")  oled_text = "S=OFF";
  
  mode_text = "M=360";
  if(no_360 == false && auto_pitch == true && auto_yaw == false)  mode_text = "M=A P";
  if(no_360 == false && auto_pitch == false && auto_yaw== true)  mode_text = "M=A Y";
  if(no_360 == true && auto_pitch == false && auto_pitch == false)  mode_text = "M=N";

  if (oled_text != previous_oled_text || previous_mode_text != mode_text) {
    oled.clearDisplay();
    oled.setTextXY(2, 1);
    oled.putString("ARNOBOT");
    oled.setTextXY(4, 1);
    oled.putString("Inspectobot,");
    oled.setTextXY(6, 1);
    oled.putString(oled_text);
    oled.setTextXY(6, 9);
    oled.putString(mode_text);
    previous_oled_text = oled_text;
    previous_mode_text = mode_text;
  }
}

void inspection_text() {
  oled_text = setting_mode;
  mode_text = inspection_request_mode;
  if (oled_text != previous_oled_text || previous_mode_text != mode_text) {
    oled.clearDisplay();
    oled.setTextXY(2, 1);
    oled.putString("Inspec Mode");
    oled.setTextXY(4, 1);
    oled.putString(oled_text);
    oled.setTextXY(6, 1);
    oled.putString(mode_text);
    previous_oled_text = oled_text; 
    previous_mode_text = mode_text;

  }
}
void text_update() {
  if (inspection_mode) {
     inspection_text();
  } else {
    default_text();
  }
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