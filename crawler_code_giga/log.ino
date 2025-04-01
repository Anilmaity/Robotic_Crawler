void serial_logs() {
  Serial.print(" ");
  Serial.print(ch[1]);
  Serial.print(" ");
  Serial.print(ch[2]);
  Serial.print(" ");
  Serial.print(ch[3]);
  Serial.print(" ");
  Serial.print(ch[4]);
  Serial.print(" ");
  // Serial.print(ch[5]);
  // Serial.print(" ");
  // Serial.print(ch[8]);
  // Serial.print(" ");
  // Serial.print(ch[9]);
  // Serial.print(" ");
  // Serial.print(ch[10]);
  // Serial.print(" ");
  // Serial.print(bot_speed);
  // Serial.print(" ");
  // Serial.print(bot_direction);
  // Serial.print(" ");
  // Serial.print(motor1_speed);
  // Serial.print(" ");
  // Serial.print(motor2_speed);
  // Serial.print(" ");
  // Serial.print(current_value);
  // Serial.print(" ");
  //Serial.print(encoder_value);
  //Serial.print(" ");


  Serial.print(" ");
  Serial.print(roll);
  Serial.print(" ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(distance_travel);
  Serial.print(" ");
  Serial.print(relay_value);
  Serial.print(" ");
  Serial.print(wifi_connected);
  Serial.print(" ");
  Serial.print(bot_mode);
  Serial.print(" "); // Serial.print(loop_time);
  // Serial.print(" ");
  // Serial.print(bot_mode);
  // Serial.print(" ");// Serial.print(" Mag: ");
  // Serial.print(JY901.stcMag.h[0]);
  // Serial.print(" ");
  // Serial.print(JY901.stcMag.h[1]);
  // Serial.print(" ");
  // Serial.print(JY901.stcMag.h[2]);


  Serial.println();
}


void comm_setup() {
    // Remap Serial2 to custom pins: TX = 42, RX = 44

    Serial3.begin(115200);  
}



void send_data() {
  

  Serial3.print(" ");
  Serial3.print(roll);
  Serial3.print(" ");
  Serial3.print(pitch);
  Serial3.print(" ");
  Serial3.print(yaw);
  Serial3.print(" ");
  Serial3.print(distance_travel);
  Serial3.print(" ");
  Serial3.print(relay_value);
  Serial3.print(" ");
  Serial3.print(wifi_connected);
  Serial3.print(" ");
  Serial3.print(bot_mode);
  Serial3.print(" "); 
  Serial3.println();
}
