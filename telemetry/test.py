import serial
import time

# Change COM port as needed (Windows: COM3, Linux: /dev/ttyUSB0)
ser = serial.Serial('COM16', 460800)

while True:
    ser.write(b'hello\n')
    print("Sent: hello")
    time.sleep(1)