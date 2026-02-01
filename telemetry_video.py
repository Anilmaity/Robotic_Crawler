import serial
import cv2
import numpy as np
import struct
import time

# ==========================
# Configuration
# ==========================
PORT = "COM16"
BAUD = 115200
TIMEOUT = 2

# For raw images (uncomment if your sender sends raw grayscale)
IMG_WIDTH = 32
IMG_HEIGHT = 32

# ==========================
# Initialize Serial
# ==========================
ser = serial.Serial(PORT, BAUD, timeout=TIMEOUT)
print("Receiving images...")

# ==========================
# Helper: Read exact number of bytes
# ==========================
def read_exact(ser, size):
    """Read exactly `size` bytes from serial or return None if failed."""
    data = b""
    start_time = time.time()
    while len(data) < size:
        packet = ser.read(size - len(data))
        if packet:
            data += packet
        else:
            # Avoid infinite loop on timeout
            if time.time() - start_time > TIMEOUT:
                return None
    return data

# ==========================
# Main loop
# ==========================
while True:
    try:
        # 1. Read 4-byte size header (big-endian)
        size_bytes = read_exact(ser, 4)
        if size_bytes is None:
            print("Failed to read image size, retrying...")
            continue

        size = struct.unpack(">I", size_bytes)[0]
        if size <= 0:
            print("Invalid image size:", size)
            continue

        # 2. Read image data
        data = read_exact(ser, size)
        if data is None or len(data) != size:
            print(f"Frame dropped! Expected {size}, got {len(data) if data else 0}")
            continue

        # ==========================
        # Option A: Compressed image (JPEG/PNG)
        # ==========================
        img = cv2.imdecode(np.frombuffer(data, dtype=np.uint8), cv2.IMREAD_GRAYSCALE)
        if img is None:
            print("Failed to decode image, skipping frame")
            continue

        # ==========================
        # Option B: Raw grayscale (uncomment if using raw)
        # ==========================
        img = np.frombuffer(data, dtype=np.uint8).reshape((IMG_HEIGHT, IMG_WIDTH))

        # 3. Display
        cv2.imshow("RFD900X Image", img)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    except KeyboardInterrupt:
        print("Exiting...")
        break
    except Exception as e:
        print("Error:", e)
        continue

ser.close()
cv2.destroyAllWindows()
