// ================= GLOBALS =================
bool firstStart = true;       // Tracks if the code just started
int relayCount = 0;           // Counts how many times CH5 > 1500
bool prevCH5High = false;     // Stores previous state of CH5 > 1500

// ================= RELAY LOGIC FUNCTION =================
void handleRelay(int relayPin, uint16_t ch5_value) {
    // Detect rising edge: only trigger when CH5 goes from low -> high
    bool ch5High = (ch5_value > 1500);

    if (ch5High && !prevCH5High) { // LOW -> HIGH transition
        relayCount++;  // increment count

        int triggerTimes = firstStart ? 2 : 4;

        for (int i = 0; i < triggerTimes; i++) {
            digitalWrite(relayPin, HIGH);
            delay(50);           // relay ON for 50ms
            digitalWrite(relayPin, LOW);
            delay(50);           // relay OFF for 50ms
        }

        firstStart = false;  // after first trigger, set firstStart false
    }

    prevCH5High = ch5High; // update previous state

    if (!ch5High){
         digitalWrite(relayPin, HIGH);

    }
}
