// ---- Serial port for packet reading ----
// For example, Arduino Mega Serial1 or Nano with SoftwareSerial
// On Mega: Serial1, on Uno/Nano: SoftwareSerial(rx, tx)

#include <Arduino.h>

uint16_t channels[4];  // decoded channels

// Function to read a full packet with sync and CRC
bool readPacket(HardwareSerial &ser) {
  while (ser.available() >= 11) {
    // Peek to find first sync byte
    if (ser.peek() == 0xAA) {
      uint8_t header[2];
      ser.readBytes(header, 2);
      if (header[1] != 0x55) {
        // Invalid second header byte, skip one byte and continue
        continue;
      }

      // Read payload + checksum
      uint8_t payload[8];
      ser.readBytes(payload, 8);
      uint8_t crc_rx = ser.read();

      // Compute XOR checksum
      uint8_t crc = 0;
      for (int i = 0; i < 8; i++) crc ^= payload[i];

      if (crc != crc_rx) {
        // Bad checksum, discard and resync
        continue;
      }

      // Decode little-endian uint16
      for (int i = 0; i < 4; i++) {
        channels[i] = payload[i*2] | (payload[i*2+1] << 8);
      }

      // Packet successfully decoded
      return true;
    } else {
      // Not sync byte, discard
      ser.read();
    }
  }
  return false;
}

void reciever_setup() {
  // Serial.begin(115200);       // USB serial for debug
  Serial2.begin(115200);      // Serial1 receives ESP32 packet
  // Serial.println("Packet Reader Ready");
}

int mapChannel(int ch) {
  ch = constrain(ch, 0, 1000);
  return (ch - 500) * 255 / 500;
}

void reciever_loop() {
  if (readPacket(Serial2)) {
    // Print decoded channels
    // Serial.print("CH1: "); Serial.print(channels[0]);
    // Serial.print(" | CH2: "); Serial.print(channels[1]);
    // Serial.print(" | CH3: "); Serial.print(channels[2]);
    // Serial.print(" | CH4: "); Serial.println(channels[3]);


    bot_speed = map(channels[2], 0, 1000, -255, 255);
    bot_direction = map(channels[0], 0, 1000, -255, 255);
  //  bot_speed     = channels[2] ;// mapChannel(channels[2]);
  // bot_direction = channels[0] ; //mapChannel(channels[0]);


    
  }
  // else{
  //   bot_speed = 0;
  //   bot_direction = 0;
  // }

}



void sbus_loop(){
  // -------- READ SBUS --------
  if (sbus_rx.Read()) {
    sbus_data = sbus_rx.data();
    last_signal_time = millis();
  }

  // // -------- PROCESS INPUT --------
  if (rc_connected && !sbus_data.failsafe) {
    int steer_pwm = sbusToPwm(sbus_data.ch[0]);     // CH1
    int throttle_pwm = sbusToPwm(sbus_data.ch[2]);  // CH3

    // ----- THROTTLE EXPO -----
    if (throttle_pwm > 1000 && throttle_pwm < 2000) {
      if (throttle_pwm >= 1500) {
        float x = (float)(throttle_pwm - 1500) / 405.0;
        bot_speed = (int)(255.0 * x * x);
      } else {
        float x = (float)(1500 - throttle_pwm) / 405.0;
        bot_speed = -(int)(255.0 * x * x);
      }
    }


    // ----- STEERING EXPO -----
    if (steer_pwm > 1000 && steer_pwm < 2000) {
      if (steer_pwm >= 1500) {
        float x = (float)(steer_pwm - 1500) / 405.0;
        bot_direction = (int)(255.0 * x * x);
      } else {
        float x = (float)(1500 - steer_pwm) / 405.0;
        bot_direction = -(int)(255.0 * x * x);
      }
    }

  } else {
    bot_speed = 0;
    bot_direction = 0;
  }

}
