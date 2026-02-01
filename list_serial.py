import serial.tools.list_ports

for port in serial.tools.list_ports.comports():
    print(f"Port: {port.device}")
    print(f"  Description: {port.description}")
    print(f"  HWID: {port.hwid}")
