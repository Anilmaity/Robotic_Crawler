

#define PIN 2  // On Trinket or Gemma, suggest changing this to 1

#define NUMPIXELS 48  // Popular NeoPixel ring size


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long int led_time = millis();

void leds_setup() {
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
}

void green() {
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();
  }
}

void red() {  pixels.clear();
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();  // Send the updated pixel colors to the hardware.
  }
}

void white() {
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    pixels.show();  // Send the updated pixel colors to the hardware.
  }
}

void blue() {
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.show();  // Send the updated pixel colors to the hardware.
  }
}

void off() {
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();  // Send the updated pixel colors to the hardware.
  }
}

void blinking(int total_delay, int speed_delay, int red, int green, int blue) {

  long int temp_time = millis();
  while (millis() - temp_time > total_delay) {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(red, green, blue));
      pixels.show();
    }
    delay(speed_delay);
  }
}

void led_control() {

  if (millis() - led_time > 3000) {
      led_time = millis();

    if (previous_bot_mode != bot_mode) {

      previous_bot_mode = bot_mode;
      if (bot_mode == "IDLE") {
        blue();
      }
      else if (bot_mode == "OFF") {
        white();
      }
      else if (bot_mode == "RUNNING") {
        green();
      }
      else if (bot_mode == "CONNECTING") {
        blue();
      }
      else if (bot_mode == "SENDING") {
        blue();
      }
      else if (bot_mode == "RC_ERROR") {
       // blinking(200, 200, 255, 0, 0);  
        red();

      }
      else if (bot_mode == "ERROR") {
        //blinking(200, 200, 255, 0, 0);   
       red();
      }
    }
  }
}