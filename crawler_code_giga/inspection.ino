

// Function to create the HTTP POST payload dynamically
String createinspectionPayload() {
  rssi = WiFi.RSSI();
  String payload = "";
  payload += "id=" + String(id);
  return payload;
}

void createinspection() {
  if (wifi_connected == true) {
    unsigned long startTime = millis();


    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Failed to reconnect to WiFi. Data update aborted.");
      wifi_connected = false;
      return;
    }

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


    // Generate data payload dynamically
    String httpRequestData = createinspectionPayload();

    String httpRequest = "POST /createinspection HTTP/1.1\r\n";
    httpRequest += "Host: " + String(serverName) + "\r\n";
    httpRequest += "Content-Type: application/x-www-form-urlencoded\r\n";
    httpRequest += "Content-Length: " + String(httpRequestData.length()) + "\r\n";
    httpRequest += "\r\n";  // End of headers
    httpRequest += httpRequestData;

    client.print(httpRequest);

    startTime = millis();
    bool successObtained = false;
    String response = "";  // Buffer to store incoming data

    while (client.connected() && (millis() - startTime < 4000)) {  // Timeout after 2 seconds
      while (client.available() && (millis() - startTime < 4000)) {                                 // Check if data is available to read
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
      
    }

    // Print final status
    if (successObtained) {
      Serial.println("\nSuccess response obtained.");
    } else {
      Serial.println("\nTimeout or different response received.");
      wifi_connected = false;
    }


  }
}




