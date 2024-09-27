#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // I2C address for OLED

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);

void oled_setup() {
  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Halt execution if OLED init fails
  }
  
  // Clear the display buffer
  display.clearDisplay();

  // Display initial "ARNOBOT" text
  displayARNOBOT();
}

void displayARNOBOT() {
  // Set text size and color
  display.setTextSize(2);               // Set text size to 2
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
  display.setCursor(0, 0);             // Set the cursor to (x, y) position (0,10)
  
  // Write "ARNOBOT" to the screen
  display.print("A");

  // Show the text on the OLED
  display.display();                    
}

void test() {


  // Display "ARNOBOT" again
  //displayARNOBOT();
}

// Function to brighten the whole screen
void brightenScreen() {
  display.clearDisplay();                // Clear the screen
  display.fillScreen(SSD1306_BLACK);     // Fill the screen with white (turn on all pixels)
  display.display();                     // Update the display to show the white screen
}

// Function to clear the OLED screen
void clearScreen() {
  display.clearDisplay();                // Clear the screen
  display.display();                     // Update the display (showing a blank screen)
}


