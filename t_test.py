# import serial
# import time
#
# READ_PORT  = "COM16"   # Receiving radio
# BAUD = 57600
#
# rx = serial.Serial(
#     READ_PORT,
#     BAUD,
#     timeout=1,
#     rtscts=False,
#     dsrdtr=False
# )
#
#
# print("Writing on COM16, reading on COM17")
#
# try:
#     counter = 0
#     while True:
#
#         # ---- READ ----
#         if rx.in_waiting:
#             data = rx.readline()
#             print("RX:", data.decode("utf-8", errors="ignore").strip())
#
#
#
# except KeyboardInterrupt:
#     print("Stopped")
#
# finally:
#     rx.close()
import cv2
import serial
import time
import struct

PORT = "COM16"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)

cap = cv2.VideoCapture(0)

print("Transmitting images...")

while True:
    ret, frame = cap.read()
    if not ret:
        continue

    # VERY SMALL IMAGE
    frame = cv2.resize(frame, (32, 32))
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # HEAVY COMPRESSION
    _, jpg = cv2.imencode(".jpg", gray, [cv2.IMWRITE_JPEG_QUALITY, 10])
    data = jpg.tobytes()

    # Send size (4 bytes)
    ser.write(struct.pack(">I", len(data)))
    time.sleep(0.05)

    # Send image data
    ser.write(data)

    print(f"Sent frame ({len(data)} bytes)")

    time.sleep(1)  # 1 frame every 5 seconds (DON'T GO LOWER)
