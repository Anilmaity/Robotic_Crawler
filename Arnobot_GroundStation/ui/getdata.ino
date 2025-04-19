#define MAX_CHANNELS 10

int ch[MAX_CHANNELS] = { 0 };     // Array to store extracted values
static String receivedData = "";  // Store received characters
long int last_message_time = 0;


void data_setup() {
  Serial4.begin(115200);
}

void data_loop() {
  static String receivedData = "";  // Store received characters


  while (Serial4.available()) {
    groundstation_connected = true;
    last_message_time = millis();
    char inChar = Serial4.read();
    if (inChar == '\n') {         // End of message
      extractData(receivedData);  // Extract and store numbers
      receivedData = "";          // Clear buffer for next message
    } else {
      receivedData += inChar;  // Append character to string
    }
  }
  if (millis() - last_message_time > 500) {
    groundstation_connected = false;
  }
}

void extractData(String data) {
  int index = 0;
  char buffer[10];  // Temporary buffer for number conversion
  int bufferIndex = 0;

  for (int i = 0; i < data.length(); i++) {
    if (data[i] == ' ' || i == data.length() - 1) {
      if (bufferIndex > 0) {
        buffer[bufferIndex] = '\0';  // Null-terminate string
        if (index < MAX_CHANNELS) {
          ch[index++] = atoi(buffer);  // Convert string to int
        }
        bufferIndex = 0;  // Reset buffer
      }
    } else {
      if (bufferIndex < 5) {  // Ensure buffer does not overflow
        buffer[bufferIndex++] = data[i];
      }
    }
  }

  // Debug: Print extracted/ values
  Serial.print("Extracted: ");
  for (int i = 1; i < MAX_CHANNELS; i++) {
  Serial.print(ch[i]);
  Serial.print(" ");
  }
  Serial.println();
}
