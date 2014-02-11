#!/usr/bin/env python3

import serial
import sys

if len(sys.argv) < 2:
    print("Usage: %s <port> [baud]" % sys.argv[0])
    exit(-1)
if len(sys.argv) > 2:
    baud = int(sys.argv[2])
else:
    baud = 57600

dev = serial.Serial(sys.argv[1], baud)
dev.timeout = 5

# Hello Message
print(dev.read(108).decode('ascii')[:-1])

while True:
    char = input("")
    if char != "quit":
        dev.write(char[0:1].encode('ascii'))
        myStream = b''
        more = True
        while more:
            c = dev.read()
            if c == b'\r':
                # End sequence is \r\n
                continue
            elif c == b'\n':
                more = False
            else:
                myStream += c
        print(myStream.decode('ascii'))
    else:
        break

dev.close()
