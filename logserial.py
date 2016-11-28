#!/usr/bin/python

import serial
serial = serial.Serial("/dev/ttyAMA0", 115200, timeout=1.5)

f = open("/home/pi/serial.log", "a+")

while True:
 data = serial.read()

 f.write(data)
 f.flush()
