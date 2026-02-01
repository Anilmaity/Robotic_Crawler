# import serial
# import struct
# import cv2
# import numpy as np
#
# PORT = "COM17"        # receiving port (change if needed)
# BAUD = 115200
#
# ser = serial.Serial(PORT, BAUD, timeout=5)
#
# print("Waiting for images...")
#
# try:
#     while True:
#         # ---- READ IMAGE SIZE (4 bytes) ----
#         size_data = ser.read(4)
#         if len(size_data) != 4:
#             continue
#
#         img_size = struct.unpack(">I", size_data)[0]
#         print(f"Receiving image of {img_size} bytes")
#
#         # ---- READ IMAGE DATA ----
#         img_bytes = b""
#         while len(img_bytes) < img_size:
#             packet = ser.read(img_size - len(img_bytes))
#             if not packet:
#                 break
#             img_bytes += packet
#
#         if len(img_bytes) != img_size:
#             print("Incomplete image received")
#             continue
#
#         # ---- DECODE JPEG ----
#         np_img = np.frombuffer(img_bytes, dtype=np.uint8)
#         img = cv2.imdecode(np_img, cv2.IMREAD_GRAYSCALE)
#
#         if img is None:
#             print("Decode failed")
#             continue
#
#         # ---- DISPLAY ----
#         cv2.imshow("RX Image", img)
#         if cv2.waitKey(1) & 0xFF == ord('q'):
#             break
#
# except KeyboardInterrupt:
#     print("Stopped")
#
# finally:
#     ser.close()
#     cv2.destroyAllWindows()


import serial

PORT = "COM17"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)

print("Waiting for messages...")

try:
    while True:
        if ser.in_waiting:
            data = ser.readline()
            print("RX:", data.decode("utf-8", errors="ignore").strip())

except KeyboardInterrupt:
    print("Stopped")

finally:
    ser.close()
