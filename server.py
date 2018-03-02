import sys
import socket
from curtsies import Input

print(sys.argv)

UDP_IP = sys.argv[1]
UDP_PORT = int(sys.argv[2])

print("UDP target IP: {0}".format(UDP_IP))
print("UDP target port: {0}".format(UDP_PORT))

# Setup
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Event loop
with Input(keynames='curses') as input_generator:
    for e in input_generator:
        sock.sendto(bytes(repr(e), "utf-8"), (UDP_IP, UDP_PORT))
        msg, __ = sock.recvfrom(1024)

        if (msg == b'\x01'):
            print('ACK from ESP32')