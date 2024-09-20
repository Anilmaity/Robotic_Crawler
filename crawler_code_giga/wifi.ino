
const unsigned long mcu_startTime = millis();  // Capture start time
const unsigned long session_id = random(1000000000, 9999999999);

// WiFi credentials
const char* ssid = "Anil";
const char* password = "9558779895";

// Server details
const char* serverName = "arnobot.live";  // Domain of your HTTP server
const int serverPort = 80;                // HTTP port

WiFiClient client;  // Use WiFiClient for HTTP

// Example sensor data (replace these with actual sensor readings)
const char* id = "96f63888-16c6-4dc5-a2ac-d5ff3e8f3117";
int power = 100;
int active_sensors = 5;
int total_sensors = 5;
int rpm = 12;
int distance = 100;
float latitude = 37.7749;
float longitude = -122.4194;
int internal_temperature = 25;
int external_temperature = 30;
float magnetic_strength = 1.2;
float voltage = 12.5;
int current_height = 1000;
int connection_speed = 500;
String rc_status = "ACTIVE";
int current_payload = 0;
bool wifi_connected = true;

bool check_hotspot(String name = "Anil") {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid != -1)

    // print the list of networks seen:
    Serial.print("number of available networks: ");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
      Serial.println(WiFi.SSID(thisNet));

    if (WiFi.SSID(thisNet) == name) {
      return true;
    }
  }

    return false;
  }


void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  if (check_hotspot()) {
    WiFi.begin(ssid, password);
    long int wait_time = millis();
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if ((millis() - wait_time) > 2000) {  // Timeout after 20 seconds
        Serial.println("\nCould not connect to WiFi!");
        wifi_connected = false;
        return;
      }
    }
    Serial.println("\nConnected to WiFi!");
    delay(1000);
  }
}

String generateSessionID() {
  // Generate a random 32-bit number and convert to string
  unsigned long randomNum = random(1000000000, 9999999999);
  return String(randomNum);
}


// Function to create the HTTP POST payload dynamically
String createPayload() {
  rssi = WiFi.RSSI();
  String payload = "";
  payload += "id=" + String(id);
  payload += "&roll=" + String(roll);
  payload += "&pitch=" + String(pitch);
  payload += "&yaw=" + String(yaw);
  payload += "&power=" + String(power);
  payload += "&active_sensors=" + String(active_sensors);
  payload += "&total_sensors=" + String(total_sensors);
  payload += "&rpm=" + String(bot_speed);
  payload += "&distance=" + String(total_steps);
  payload += "&latitude=" + String(latitude, 6);    // 6 decimal places for precision
  payload += "&longitude=" + String(longitude, 6);  // 6 decimal places for precision
  payload += "&internal_temp=" + String(internal_temperature);
  payload += "&external_temp=" + String(external_temperature);
  payload += "&magnetic_strength=" + String(magnetic_strength);
  payload += "&volt=" + String(voltage);
  payload += "&height=" + String(current_height);
  payload += "&connection_speed=" + String(rssi) + " dBm";
  payload += "&rc_status=" + rc_status;
  payload += "&current_payload=" + String(current_payload);
  payload += "&elapsed_time=" + String(millis() - mcu_startTime);
  payload += "&session_id=" + String(session_id);

  return payload;
}

void updateData() {
  if (wifi_connected == true) {
    unsigned long startTime = millis();

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi Disconnected. Reconnecting...");
      //connectToWiFi();
      if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Failed to reconnect to WiFi. Data update aborted.");
        wifi_connected = false;
        return;
      }
    }
    // Serial.println("Time Taken to check and connect Wifi");
    // Serial.println(millis() - startTime);
    startTime = millis();

    if (!client.connected()) {

      while (!client.connect(serverName, serverPort)) {
        if (millis() - startTime > 1000) {  // Timeout after 1 seconds
          Serial.println("Connection to HTTP server failed.");
          wifi_connected = false;
          return;
        }
      }
    }


    // Serial.println("Time Taken to connect to server");
    // Serial.println(millis() - startTime);
    // startTime = millis();


    // Generate data payload dynamically
    String httpRequestData = createPayload();

    String httpRequest = "POST /botlog HTTP/1.1\r\n";
    httpRequest += "Host: " + String(serverName) + "\r\n";
    httpRequest += "Content-Type: application/x-www-form-urlencoded\r\n";
    httpRequest += "Content-Length: " + String(httpRequestData.length()) + "\r\n";
    httpRequest += "\r\n";  // End of headers
    httpRequest += httpRequestData;

    // HTTP POST request length and send payload
    client.print(httpRequest);
    // Serial.println("Time Taken to send request");
    // Serial.println(millis() - startTime);

    startTime = millis();
    bool successObtained = false;
    String response = "";  // Buffer to store incoming data

    while (client.connected() && (millis() - startTime < 1000)) {  // Timeout after 2 seconds
      while (client.available()) {                                 // Check if data is available to read
        char c = client.read();                                    // Read one byte at a time
        response += c;                                             // Append byte to the response buffer
        // Serial.print(c);                                           // Print each character for debugging

        // Check for the desired response
        if (response.indexOf("{\"success\":true}") != -1) {
          successObtained = true;
          break;  // Exit inner loop if the response is found
        }
      }

      // Break outer loop if the response is found
      if (successObtained) {
        break;
      }

      // Allow other tasks to run (important in embedded systems)
      yield();
    }

    // Print final status
    if (successObtained) {
      Serial.println("\nSuccess response obtained.");
    } else {
      Serial.println("\nTimeout or different response received.");
    }

    // Serial.println("Time Taken to obtain response");
    // Serial.println(millis() - startTime);
  }
}




  void printEncryptionType(int thisType) {
    // read the encryption type and print out the name:
    switch (thisType) {
      case ENC_TYPE_WEP:
        Serial.print("WEP");
        break;
      case ENC_TYPE_WPA:
        Serial.print("WPA");
        break;
      case ENC_TYPE_WPA2:
        Serial.print("WPA2");
        break;
      case ENC_TYPE_NONE:
        Serial.print("None");
        break;
      case ENC_TYPE_AUTO:
        Serial.print("Auto");
        break;
      case ENC_TYPE_WPA3:
        Serial.print("WPA3");
        break;
      case ENC_TYPE_UNKNOWN:
      default:
        Serial.print("Unknown");
        break;
    }
  }

  void print2Digits(byte thisByte) {
    if (thisByte < 0xF) {
      Serial.print("0");
    }
    Serial.print(thisByte, HEX);
  }

  void printMacAddress(byte mac[]) {
    for (int i = 0; i < 6; i++) {
      if (i > 0) {
        Serial.print(":");
      }
      if (mac[i] < 16) {
        Serial.print("0");
      }
      Serial.print(mac[i], HEX);
    }
    Serial.println();
  }