#include <iBus.h>

#define MAX_CHANNELS 10

iBus receiver(Serial4, MAX_CHANNELS);  // Serial2 pins in arduino giga
                                     
void ibus_setup() {
  receiver.begin();
}

void ibus_loop() {
  receiver.process();

  for(byte i = 1; i <= MAX_CHANNELS; i++){  // get channel values starting from 1
  int value = receiver.get(i);
  if(value >= 1000 && value <= 2000)
  {
    ch[i] = value;
  }
    //Serial.print(receiver.get(i));
    //Serial.print('\t');
  }
  //Serial.println(receiver.get(0));  // received packet quality. If 0 -> there are some corrupted values

if (ch[5] >= 1200) {

    if (ch[3] <= 2000 && ch[3] >= 1000) {

      bot_speed = map(ch[3], 1000, 2000, 500, -500);

    }
     else{
      bot_speed = 0;
    }


    if (ch[1] <= 2000 && ch[1] >= 1000) {
      bot_direction = map(ch[1], 1000, 2000, -350, 350);  // 912
    } else {
      bot_direction = 0;  // 912
    }

    if(ch[6] <= 2000 && ch[6] >= 1000){
      if (ch[6] > 1200)
      {
      speed_setting = 505;
      }
      else{
        speed_setting = 600;

      }
    }
    


  }else {
    bot_speed = 0;
  }

}



