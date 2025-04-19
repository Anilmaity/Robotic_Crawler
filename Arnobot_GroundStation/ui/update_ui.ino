void update_ui() {
  roll = ch[0];
  pitch = ch[1];
  yaw = ch[2];
  distance = ch[3];
  headlight = ch[4];
  wifi = ch[5];
  bot_mode = ch[6];
  encorder_connected = ch[7];
  if (String(roll) == "0.00" && String(pitch) == "0.00" & String(yaw) == "0.00") {
    lv_label_set_text(ui_imuStatus, String("disconnected").c_str());
    lv_obj_set_style_bg_color(ui_imuIndicator, lv_color_hex(0xFF0000), LV_PART_MAIN);  // Set Red color
  } else {
    lv_label_set_text(ui_imuStatus, String("connected").c_str());
    lv_obj_set_style_bg_color(ui_imuIndicator, lv_color_hex(0x00FF00), LV_PART_MAIN);  // Set Red color
  }

  lv_label_set_text(ui_rollValue, String(roll).c_str());
  lv_label_set_text(ui_pitchValue, String(pitch).c_str());
  lv_label_set_text(ui_yawValue, String(yaw).c_str());




  if (String(encorder_connected) == "0") {
    lv_label_set_text(ui_encoderStatus, String("disconnected").c_str());
    lv_obj_set_style_bg_color(ui_encoderIndicator, lv_color_hex(0xFF0000), LV_PART_MAIN);  // Set Red color
    lv_label_set_text(ui_encoderValue, (String(0) + " m").c_str());
  } else {
    lv_label_set_text(ui_encoderStatus, String("connected").c_str());
    lv_obj_set_style_bg_color(ui_encoderIndicator, lv_color_hex(0x00FF00), LV_PART_MAIN);  // Set Red color
    lv_label_set_text(ui_encoderValue, (String(distance) + " m").c_str());
  }


  if (String(headlight) == "0") {
    lv_obj_clear_state(ui_headlightValue, LV_STATE_CHECKED);  // Turn ON
  } else {

    lv_obj_add_state(ui_headlightValue, LV_STATE_CHECKED);  // Turn OFF
  }

  if (String(wifi) == "0") {
    lv_label_set_text(ui_wifiStatus, String("disconnected").c_str());
    lv_obj_set_style_bg_color(ui_wifiIndicator, lv_color_hex(0xFF0000), LV_PART_MAIN);  // Set Red color
  } else {
    lv_label_set_text(ui_wifiStatus, String("connected").c_str());
    lv_obj_set_style_bg_color(ui_wifiIndicator, lv_color_hex(0x00FF00), LV_PART_MAIN);  // Set Red color
  }
  //   else if (bot_mode == "AT") botinfo = 3;
  // else if (bot_mode == "N") botinfo = 4;
  // else if (bot_mode == "360") botinfo = 5;
  if (String(bot_mode) == "3") {
    lv_tabview_set_act(ui_mode, 0, LV_ANIM_ON);  // Switch to 1 tab)

  } else if (String(bot_mode) == "5") {
    lv_tabview_set_act(ui_mode, 1, LV_ANIM_ON);  // Switch to 2 tab)

  } else if (String(bot_mode) == "4") {
    lv_tabview_set_act(ui_mode, 2, LV_ANIM_ON);  // Switch to 1 tab)
  }
  

  if (groundstation_connected == false) {
    lv_label_set_text(ui_groundstationStatus, String("altius disconnected").c_str());
    lv_obj_set_style_bg_color(ui_groundstationIndicator, lv_color_hex(0xFF0000), LV_PART_MAIN);  // Set Red color
  } else {
    lv_label_set_text(ui_groundstationStatus, String("altius connected").c_str());
    lv_obj_set_style_bg_color(ui_groundstationIndicator, lv_color_hex(0x00FF00), LV_PART_MAIN);  // Set Red color
  }

  lv_timer_handler();
  delay(50);
}



void logs() {

  Serial.print(roll);
  Serial.print(" ");
  Serial.print(pitch);
  Serial.print(" ");
  Serial.print(yaw);
  Serial.print(" ");
  Serial.print(distance);
  Serial.print(" ");
  Serial.print(headlight);
  Serial.print(" ");
  Serial.print(wifi);
  Serial.print(" ");
  Serial.print(bot_mode);
  Serial.print(" ");
  Serial.print(groundstation_connected);
  Serial.print(" ");
  Serial.println();
}
