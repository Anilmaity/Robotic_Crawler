#include "Arduino_H7_Video.h"
#include "Arduino_GigaDisplayTouch.h"
#include "lvgl.h"
#include <ui.h>
// #include <ArduinoWebsockets.h
#include <WiFi.h>
#include <WiFiClient.h>
#include "Arduino.h"


const char* serverName = "arnobot.live";  // Domain of your HTTP server
const int serverPort = 80;
const char* id = "96f63888-16c6-4dc5-a2ac-d5ff3e8f3117";
WiFiClient client;  // Use WiFiClient for HTTP

float roll = 1.00;
float pitch = 2.00;
float yaw = 3.00;
float distance = 4.00;
int headlight = 0;
int wifi= 0 ;
int bot_mode = 0;
int groundstation_connected = false;
int encorder_connected = 0;
bool wifi_connected = true;
long rssi = 0;  // Get the RSSI value
int current_value = 0;
int bot_speed = 0;
int distance_travel = 0;
long int update_data = 0;


Arduino_H7_Video Display( 800, 480, GigaDisplayShield ); //( 800, 480, GigaDisplayShield );
Arduino_GigaDisplayTouch TouchDetector;

void setup() {
  Display.begin();
  TouchDetector.begin();
  data_setup();
  ui_init();

  connectToWiFi(); 

}

void loop()
{

  data_loop();
  update_ui();
  logs();
   if (millis() - update_data > 1000) {
     updateData(); 

    //Serial.println(millis() - update_data);
    update_data = millis();
  }


}
