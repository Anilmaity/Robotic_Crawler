import cv2
import serial
import struct
import numpy as np
import time

COM_PORT = "COM16"
BAUD = 460800

# Desired display size
DISPLAY_WIDTH = 320
DISPLAY_HEIGHT = 240

print("Opening telemetry port...")

try:
    ser = serial.Serial(COM_PORT, BAUD, timeout=0)
    print("Telemetry connected on", COM_PORT)
except Exception as e:
    print("Failed to open telemetry:", e)
    exit()

print("Receiving video...")

buffer = b''
frame_counter = 0
start_time = time.time()

while True:
    buffer += ser.read(ser.in_waiting or 1)

    while True:
        start = buffer.find(b'\xAA\x55')
        if start == -1:
            break

        if len(buffer) < start + 4:
            break

        size = struct.unpack(">H", buffer[start+2:start+4])[0]

        if len(buffer) < start + 4 + size:
            break

        frame_data = buffer[start+4:start+4+size]
        buffer = buffer[start+4+size:]

        img = np.frombuffer(frame_data, dtype=np.uint8)

        try:
            frame = cv2.imdecode(img, 1)
            if frame is None:
                continue
        except:
            continue

        # ----------------------------
        # Resize frame before showing
        # ----------------------------
        frame = cv2.resize(frame, (DISPLAY_WIDTH, DISPLAY_HEIGHT), interpolation=cv2.INTER_LINEAR)

        cv2.imshow("Telemetry Video", frame)
        frame_counter += 1

    # FPS counter
    if time.time() - start_time >= 1:
        print("Received FPS:", frame_counter)
        frame_counter = 0
        start_time = time.time()

    if cv2.waitKey(1) == 27:  # ESC to exit
        break

cv2.destroyAllWindows()