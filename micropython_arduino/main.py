from machine import Pin
import time

# Try LED_BUILTIN instead of 13 if 13 gives an error
led = Pin(13, Pin.OUT)

while True:
    led.value(1)
    print("LED ON")
    time.sleep(0.5)

    led.value(0)
    print("LED OFF")
    time.sleep(0.5)
#
# import network
# import time
#
# # Replace with your Wi-Fi credentials
# SSID = "Arnobot"
# PASSWORD = "Altius01"
#
# # Create station interface
# wlan = network.WLAN(network.STA_IF)
# wlan.active(True)
#
# # Connect to Wi-Fi
# if not wlan.isconnected():
#     print("Connecting to Wi-Fi...")
#     wlan.connect(SSID, PASSWORD)
#
#     # Wait for connection with timeout
#     timeout = 10  # seconds
#     start = time.time()
#
#     while not wlan.isconnected():
#         if time.time() - start > timeout:
#             print("❌ Failed to connect to Wi-Fi")
#             break
#         time.sleep(1)
#
# # Print network info
# if wlan.isconnected():
#     print("✅ Connected to Wi-Fi")
#     print("IP address:", wlan.ifconfig()[0])
# else:
#     print("Not connected.")
