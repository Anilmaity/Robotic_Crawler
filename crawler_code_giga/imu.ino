void imu() {

  while (Serial2.available()) {
    JY901.CopeSerialData(Serial2.read());  //Call JY901 data cope function
  }


  roll =  (float)JY901.stcAngle.Angle[0] / 32768 * 180;
  pitch = (float)JY901.stcAngle.Angle[1] / 32768 * 180;


  // if (abs(roll - (float)JY901.stcAngle.Angle[0] / 32768 * 180) > 90) {
  //   roll = roll;
  // } else {
  //   roll =  (float)JY901.stcAngle.Angle[0] / 32768 * 180;
  // }

  // if (abs(pitch - (float)JY901.stcAngle.Angle[1] / 32768 * 180) > 90) {
  //   pitch = pitch;
  // } else {
  //   pitch = (float)JY901.stcAngle.Angle[1] / 32768 * 180;
  // }

  if (abs(yaw - (float)JY901.stcAngle.Angle[2] / 32768 * 180) > 100) {
    yaw = yaw;
  } else {
    yaw = 0.5 * yaw + 0.5 * (float)JY901.stcAngle.Angle[2] / 32768 * 180;
  }


}