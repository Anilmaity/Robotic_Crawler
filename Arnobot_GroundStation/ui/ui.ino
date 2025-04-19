#include "Arduino_H7_Video.h"
#include "Arduino_GigaDisplayTouch.h"
#include "lvgl.h"
#include <ui.h>
float roll = 1.00;
float pitch = 2.00;
float yaw = 3.00;
float distance = 4.00;
int headlight = 0;
int wifi= 0 ;
int bot_mode = 0;
int groundstation_connected = false;
int encorder_connected = 0;
Arduino_H7_Video Display( 800, 480, GigaDisplayShield ); //( 800, 480, GigaDisplayShield );
Arduino_GigaDisplayTouch TouchDetector;

void setup() {
  Display.begin();
  TouchDetector.begin();
  data_setup();

  ui_init();
}

void loop()
{

  data_loop();
  update_ui();
  //logs();

}
