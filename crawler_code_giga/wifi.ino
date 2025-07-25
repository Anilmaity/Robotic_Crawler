
// const unsigned long mcu_startTime = millis();  // Capture start time
// const unsigned long session_id = random(1000000000, 9999999999);

// // WiFi credentials
// const char* ssid = "AnilMaity";
// const char* password = "12345678";
// const char* ssid2 = "ARS";
// const char* password2 = "9925512860";
// const char* ssid3 = "Anmol's Iphone 2";
// const char* password3 = "Anmolshah";

//             // HTTP port


// // Example sensor data (replace these with actual sensor readings)
// int power = 100;
// int active_sensors = 5;
// int total_sensors = 5;
// int rpm = 12;
// int distance = 100;
// float latitude = 37.7749;
// float longitude = -122.4194;
// int internal_temperature = 25;
// int external_temperature = 30;
// float magnetic_strength = 1.2;
// float voltage = 48;
// int current_height = 1000;
// int connection_speed = 500;
// String rc_status = "ACTIVE";
// int current_payload = 0;

// struct HotspotCredentials {
//   String ssid;
//   String password;
// };

// // Function to check and return the hotspot credentials
// HotspotCredentials check_hotspot(String preferred_ssid = "Anil") {
//   Serial.println("** Scan Networks **");
//   int numSsid = WiFi.scanNetworks();
//   if (numSsid == -1) {
//     Serial.println("No networks found");
//     return { "", "" };  // Return empty if no networks found
//   }

//   Serial.print("Number of available networks: ");
//   Serial.println(numSsid);

//   // Loop through the available networks
//   for (int thisNet = 0; thisNet < numSsid; thisNet++) {
//     Serial.println(WiFi.SSID(thisNet));

//     if (WiFi.SSID(thisNet) == String(ssid)) {
//       return { ssid, password };
//     } else if (WiFi.SSID(thisNet) == String(ssid2)) {
//       return { ssid2, password2 };
//     } else if (WiFi.SSID(thisNet) == String(ssid3)) {
//       return { ssid3, password3 };
//     }
//   }

//   return { "", "" };  // Return empty if none of the networks match
// }



// void connectToWiFi() {
//   Serial.print("Connecting to WiFi...");
//   wifi_connected = false;

//   HotspotCredentials creds = check_hotspot();

//   if (creds.ssid != "") {
//     Serial.print("Connecting to SSID: ");
//     Serial.println(creds.ssid);
//     long int wait_time = millis();

//     WiFi.begin(creds.ssid.c_str(), creds.password.c_str());

//     while (WiFi.status() != WL_CONNECTED && (millis() - wait_time) < 5000) {
//       Serial.print(".");
//     }
//     if (WiFi.status() == WL_CONNECTED) {

//       wifi_connected = true;
//       Serial.println("\nConnected to WiFi!");
//     } else {

//       Serial.println("Timeout .");
//     }
//   }

//   // Connect using creds.ssid and creds.password
//   else {

//     Serial.println("No matching hotspot found.");
//   }
//   delay(1000);

// }



// String generateSessionID() {
//   // Generate a random 32-bit number and convert to string
//   unsigned long randomNum = random(1000000000, 9999999999);
//   return String(randomNum);
// }


// // Function to create the HTTP POST payload dynamically
// String createPayload() {
//   rssi = WiFi.RSSI();
//   String payload = "";
//   payload += "id=" + String(id);
//   payload += "&roll=" + String(roll);
//   payload += "&pitch=" + String(pitch);
//   payload += "&yaw=" + String(yaw);
//   payload += "&power=" + String(int(current_value * 1.39));
//   payload += "&active_sensors=" + String(active_sensors);
//   payload += "&total_sensors=" + String(total_sensors);
//   payload += "&rpm=" + String(bot_speed);
//   payload += "&distance=" + String((distance_travel));
//   payload += "&latitude=" + String(latitude, 6);    // 6 decimal places for precision
//   payload += "&longitude=" + String(longitude, 6);  // 6 decimal places for precision
//   payload += "&internal_temp=" + String(internal_temperature);
//   payload += "&external_temp=" + String(external_temperature);
//   payload += "&magnetic_strength=" + String(magnetic_strength);
//   payload += "&volt=" + String(voltage);
//   payload += "&height=" + String(current_height);
//   payload += "&connection_speed=" + String(rssi) + " dBm";
//   payload += "&rc_status=" + rc_status;
//   payload += "&current_payload=" + String(current_payload);
//   payload += "&elapsed_time=" + String(millis() - mcu_startTime);
//   payload += "&session_id=" + String(session_id);

//   return payload;
// }

// void updateData() {
//   if (wifi_connected == true) {
//     unsigned long startTime = millis();


//     if (WiFi.status() != WL_CONNECTED) {
//       Serial.println("Failed to reconnect to WiFi. Data update aborted.");
//       wifi_connected = false;
//       return;
//     }
//     // Serial.println("Time Taken to check and connect Wifi");
//     // Serial.println(millis() - startTime);
//     startTime = millis();

//     if (!client.connected()) {

//       while (!client.connect(serverName, serverPort)) {
//         if (millis() - startTime > 1000) {  // Timeout after 1 seconds
//           Serial.println("Connection to HTTP server failed.");
//           wifi_connected = false;
//           return;
//         }
//       }
//     }


//     // Serial.println("Time Taken to connect to server");
//     // Serial.println(millis() - startTime);
//     // startTime = millis();


//     // Generate data payload dynamically
//     String httpRequestData = createPayload();

//     String httpRequest = "POST /botlog HTTP/1.1\r\n";
//     httpRequest += "Host: " + String(serverName) + "\r\n";
//     httpRequest += "Content-Type: application/x-www-form-urlencoded\r\n";
//     httpRequest += "Content-Length: " + String(httpRequestData.length()) + "\r\n";
//     httpRequest += "\r\n";  // End of headers
//     httpRequest += httpRequestData;

//     // HTTP POST request length and send payload
//     client.print(httpRequest);
//     // Serial.println("Time Taken to send request");
//     // Serial.println(millis() - startTime);

//     startTime = millis();
//     bool successObtained = false;
//     String response = "";  // Buffer to store incoming data

//     while (client.connected() && (millis() - startTime < 4000)) {  // Timeout after 2 seconds
//       while (client.available() && (millis() - startTime < 4000)) {                                 // Check if data is available to read
//         char c = client.read();                                    // Read one byte at a time
//         response += c;                                             // Append byte to the response buffer
//         // Serial.print(c);                                           // Print each character for debugging

//         // Check for the desired response
//         if (response.indexOf("{\"success\":true}") != -1) {
//           successObtained = true;
//           break;  // Exit inner loop if the response is found
//         }  
//       move_bot();

//       }

//       // Break outer loop if the response is found
//       if (successObtained) {
//         break;
//       }
//       move_bot();
      
//     }

//     // Print final status
//     if (successObtained) {
//       Serial.println("\nSuccess response obtained.");
//     } else {
//       Serial.println("\nTimeout or different response received.");
//       wifi_connected = false;
//     }

//     // Serial.println("Time Taken to obtain response");
//     // Serial.println(millis() - startTime);
//   }
// }




// void printEncryptionType(int thisType) {
//   // read the encryption type and print out the name:
//   switch (thisType) {
//     case ENC_TYPE_WEP:
//       Serial.print("WEP");
//       break;
//     case ENC_TYPE_WPA:
//       Serial.print("WPA");
//       break;
//     case ENC_TYPE_WPA2:
//       Serial.print("WPA2");
//       break;
//     case ENC_TYPE_NONE:
//       Serial.print("None");
//       break;
//     case ENC_TYPE_AUTO:
//       Serial.print("Auto");
//       break;
//     case ENC_TYPE_WPA3:
//       Serial.print("WPA3");
//       break;
//     case ENC_TYPE_UNKNOWN:
//     default:
//       Serial.print("Unknown");
//       break;
//   }
// }

// void print2Digits(byte thisByte) {
//   if (thisByte < 0xF) {
//     Serial.print("0");
//   }
//   Serial.print(thisByte, HEX);
// }

// void printMacAddress(byte mac[]) {
//   for (int i = 0; i < 6; i++) {
//     if (i > 0) {
//       Serial.print(":");
//     }
//     if (mac[i] < 16) {
//       Serial.print("0");
//     }
//     Serial.print(mac[i], HEX);
//   }
//   Serial.println();
// }