

import serial
import time

ser = serial.Serial("COM16", 57600, timeout=1)
time.sleep(2)  # important for USB-serial devices

counter = 0
try:
    while True:
        msg = f"Hello {counter}\n"
        ser.write(msg.encode("utf-8"))
        counter += 1
        time.sleep(0.5)
        print(msg)
finally:
    ser.close()