#include <WiFi.h>

// WiFi credentials
const char* ssid = "Anil";
const char* password = "9558779895";

// Server details
const char* serverName = "http://192.168.1.4:8000";

bool connected = false;

// Function to connect to WiFi
void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  long int wait_time = millis();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    connected = true;
 
    if((millis() - wait_time) > 20000){
      connected = false;
      break;
    }

    if(connected){
    Serial.println("\nConnected to WiFi!");

    }
    else{
    Serial.println("\nCould not Connect to WiFi!");

    }

  }
  delay(1000);

}


void updateData() {
  Serial.print("Updating Data to cloud");
  delay(100);

}



