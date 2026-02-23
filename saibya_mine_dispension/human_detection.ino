 /*!
  * @file  mRangeVelocity.ino
  * @brief  radar measurement demo
  * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  * @license The MIT License (MIT)
  * @author ZhixinLiu(zhixin.liu@dfrobot.com)
  * @version V1.0
  * @date 2024-02-02
  * @url https://github.com/dfrobot/DFRobot_C4001
  */

#include "DFRobot_C4001.h"



DFRobot_C4001_UART radar(&Serial2 ,9600);


void rad_setup()
{
 
  while(!radar.begin()){
    Serial.println("NO Deivces !");
    delay(1000);
  }
  Serial.println("Device connected!");

  // speed Mode
  // radar.setSensorMode(eSpeedMode);

  sSensorStatus_t data;
  data = radar.getStatus();
  //  0 stop  1 start
  Serial.print("work status  = ");
  Serial.println(data.workStatus);

  //  0 is exist   1 speed
  Serial.print("work mode  = ");
  Serial.println(data.workMode);

  //  0 no init    1 init success
  Serial.print("init status = ");
  Serial.println(data.initStatus);
  Serial.println();


  // if(radar.setDetectThres(/*min*/15, /*max*/1200, /*thres*/100)){
  //   Serial.println("set detect threshold successfully");
  // }

  // set Fretting Detection
  // radar.setFrettingDetection(eON);
  
  // get confige params
  // Serial.print("min range = ");
  // Serial.println(radar.getTMinRange());
  // Serial.print("max range = ");
  // Serial.println(radar.getTMaxRange());
  // Serial.print("threshold range = ");
  // Serial.println(radar.getThresRange());
  // Serial.print("fretting detection = ");
  // Serial.println(radar.getFrettingDetection());
}

void rad_loop()
{
    human = radar.getTargetNumber();


  Serial.print(" target number = ");
  Serial.print(human);   // must exist
  Serial.print(" target Speed  = ");
  Serial.print(radar.getTargetSpeed());
  Serial.print(" m/s");

  Serial.print(" target range  = ");
  Serial.print(radar.getTargetRange());
  Serial.print(" m");

  Serial.print(" target energy  = ");
  Serial.println(radar.getTargetEnergy());
  // delay(100);

  if (human > 0){
    human_detected = true;
  }
}