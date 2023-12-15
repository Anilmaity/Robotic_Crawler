#include <IBusBM.h>


IBusBM IBus; // IBus object

void ibus_setup() {

  IBus.begin(Serial3);    // iBUS connected to Serial0 - change to Serial1 or Serial2 port when required


  Serial.println("Start IBus2PWM");
}   


void ibus_loop() {

  
  // Getting values form all channel
  for (int i = 0; i <= 8 ; i++)
  {
   channel_data[i] = IBus.readChannel(i); // get latest value for servo channel 1
   Serial.print(channel_data[i]);
    //Serial.print(Serial3.available());
   Serial.print(" ");
  } 
  //Serial.println();

  //-------------------------forward backward---------------------
    if (channel_data[2] <= 2000 && channel_data[2] >= 1000) {
      bot_speed = map(channel_data[2], 1000, 2000 , -255 , 255);
    }
    else{
      bot_speed=0;
    }

    //-------------------------Direction---------------------
    if (channel_data[0] <= 2000 && channel_data[0] >= 1000) {
      bot_direction = map(channel_data[0], 1000, 2000 , -125 , 125);
    }
    else{
      bot_direction=0;
    }


  delay(10);
}
