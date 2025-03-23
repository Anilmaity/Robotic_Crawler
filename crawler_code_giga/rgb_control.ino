

#define PIN 7  // On Trinket or Gemma, suggest changing this to 1
// #define PIN2 5 // On Trinket or Gemma, suggest changing this to 1
// #define NUMPIXELS2 32  // Popular NeoPixel ring size

#define NUMPIXELS 32  // Popular NeoPixel ring size
int max_brightness = 255;
int start_led = 1;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel pixels2(NUMPIXELS, PIN2, NEO_GRB + NEO_KHZ800);

long int led_time = millis();

void leds_setup() {
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
  off();
  // pixels2.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)

}

void green() {
  //pixels.clear();
  //off();
  for (int i = start_led; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();
}    

  // for (int i = 0; i < NUMPIXELS2; i++) {
  //   pixels2.setPixelColor(i, pixels2.Color(0, 200, 0));
  //   pixels2.show();
  // }
}

void red() {  
  // pixels2.clear();
  off();

  for (int i = start_led; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();  // Send the updated pixel colors to the hardware.
  }
  // for (int i = 0; i < NUMPIXELS2; i++) {
  //   pixels2.setPixelColor(i, pixels2.Color(200, 0, 0));
  //   pixels2.show();
  // }
}

void white() {
  off();

  for (int i = start_led; i < NUMPIXELS; i++) {  // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    pixels.show();  // Send the updated pixel colors to the hardware.
  }
  // for (int i = 0; i < NUMPIXELS2; i++) {  // For each pixel...
  //   pixels2.setPixelColor(i, pixels2.Color(200, 200, 200));
  //   pixels2.show();  // Send the updated pixel colors to the hardware.
  // }
}

void blue() {
  off();


  for (int i = start_led; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
  }
    pixels.show();  // Send the updated pixel colors to the hardware.
//   for (int i = 0; i < NUMPIXELS; i++) {
//     pixels2.setPixelColor(i, pixels2.Color(0, 0, 200));
//     pixels2.show();  // Send the updated pixel colors to the hardware.
//   }
}

void off() {
  pixels.clear();
  // pixels2.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  //   pixels.show();  // Send the updated pixel colors to the hardware.
  // for (int i = 0; i < NUMPIXELS; i++) {
  //   pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
  //   pixels2.show();  // Send the updated pixel colors to the hardware.
  // }
}

void blinking(int total_delay, int speed_delay, int red, int green, int blue) {

  long int temp_time = millis();
  while (millis() - temp_time > total_delay) {
    for (int i = start_led; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(red, green, blue));
      pixels.show();
    }
    delay(speed_delay);
  }
}

void led_control() {

  if (millis() - led_time > 1000) {
      led_time = millis();

    if (previous_bot_mode != bot_mode  ) {
 
      previous_bot_mode = bot_mode;
      if (bot_mode == "IDLE") {
        //off();        
        blue();


      }
      else if (bot_mode == "OFF") {
        //off();        
        white();      


      }
      else if (bot_mode == "RUNNING") {
        //off();        
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
      else if (bot_mode == "LIGHT_OFF") {
        //blinking(200, 200, 255, 0, 0);   
        off();        


      }
    }
  }
}