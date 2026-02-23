

// ---------- MAVLINK IDs ----------
#define SYS_ID   42
#define COMP_ID  1

// ---------- BATTERY SIM ----------
float battery_voltage = 12.6;
int   battery_percent = 100;

// ---------- SETUP ----------
void gps_setup() {
  Serial2.begin(38400);     // GPS baud rate (IMPORTANT)
}

// ---------- LOOP ----------
void gps_loop() {

  // READ GPS DATA
  while (Serial2.available() > 0)
  {
    char c = Serial2.read();
    gps.encode(c);
  }

  static unsigned long lastMav = 0;
  if (millis() - lastMav >= 200) {   // ~5Hz
    lastMav = millis();

    // ALWAYS SEND THESE
    sendHeartbeat();

    // ONLY SEND GPS DATA IF VALID
    if (gps.location.isValid() && gps.location.lat() != 0) {
      sendGpsData();

      // Serial.print("GPS OK -> ");
      // Serial.print(gps.location.lat(), 6);
      // Serial.print(", ");
      // Serial.println(gps.location.lng(), 6);


    } else {
      sendBattery();

      Serial.println("GPS LOST -> Telemetry still alive");
    }
        sendHeartbeat();
        sendBattery();

  }
}

// ---------- HEARTBEAT ----------
void sendHeartbeat() {
  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
  mavlink_message_t msg;

  mavlink_msg_heartbeat_pack(
    SYS_ID,
    COMP_ID,
    &msg,
    MAV_TYPE_QUADROTOR,
    MAV_AUTOPILOT_ARDUPILOTMEGA,
    MAV_MODE_MANUAL_ARMED,
    0,
    MAV_STATE_ACTIVE
  );

  uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
  Serial3.write(buffer, len);
}

// ---------- GPS DATA (ONLY WHEN VALID) ----------
void sendGpsData() {
  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
  mavlink_message_t msg;
  uint16_t len;

  int32_t lat = gps.location.lat() * 1e7;
  int32_t lon = gps.location.lng() * 1e7;
  int32_t alt = gps.altitude.meters() * 1000;
  int16_t vx  = gps.speed.mps() * 100;
  uint16_t hdg = gps.course.deg() * 100;

  // GLOBAL POSITION
  mavlink_msg_global_position_int_pack(
    SYS_ID,
    COMP_ID,
    &msg,
    millis(),
    lat,
    lon,
    alt,
    alt,
    vx,
    0,
    0,
    hdg
  );
  len = mavlink_msg_to_send_buffer(buffer, &msg);
  Serial3.write(buffer, len);

  // VFR HUD
  mavlink_msg_vfr_hud_pack(
    SYS_ID,
    COMP_ID,
    &msg,
    gps.speed.mps(),
    gps.speed.mps(),
    gps.course.deg(),
    50,
    gps.altitude.meters(),
    0
  );
  len = mavlink_msg_to_send_buffer(buffer, &msg);
  Serial3.write(buffer, len);
}

// ---------- BATTERY / SYSTEM STATUS (ALWAYS SENT) ----------
void sendBattery() {
  uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
  mavlink_message_t msg;

  battery_voltage = v4;
  if (battery_voltage < 10.5) battery_voltage = 12.6;

  mavlink_msg_sys_status_pack(
    SYS_ID,
    COMP_ID,
    &msg,
    0, 0, 0,
    500,
    (uint16_t)(battery_voltage * 1000),
    100,
    (int8_t)battery_percent,
    0, 0, 0, 0, 0, 0, 0, 0, 0
  );

  uint16_t len = mavlink_msg_to_send_buffer(buffer, &msg);
  Serial3.write(buffer, len);
}
