
void send_data(){

      Serial3.println();
    Serial3.print("DATA:");
    if (sbusToPwm(sbus_data.ch[8]) > 1500) {
      Serial3.print(0);

    } else {
      Serial3.print(1);
    }
    Serial3.print(" ");
    if (sbusToPwm(sbus_data.ch[9]) > 1500) {
      Serial3.print(0);

    } else {
      Serial3.print(1);
    }

    Serial3.print(" ");
    if (sbusToPwm(sbus_data.ch[4]) > 1300 &&  sbusToPwm(sbus_data.ch[4]) < 1700) {
      Serial3.print(0);

    } else if(sbusToPwm(sbus_data.ch[4]) < 1300) {
      Serial3.print(1);
    }
    else{
        Serial3.print(2);
    }

    Serial3.print(" ");
    if (sbusToPwm(sbus_data.ch[5]) > 1300 &&  sbusToPwm(sbus_data.ch[5]) < 1700) {
      Serial3.print(0);

    } else if(sbusToPwm(sbus_data.ch[5]) < 1300) {
      Serial3.print(1);
    }
    else{
        Serial3.print(2);
    }
    Serial3.println(" ");
  }
