#!/usr/bin/python
import serial
import os
ser = serial.Serial('/dev/ttyACM0', 9600)
while 1:
	temp = ser.readline()
	print(temp)
	data_package="wget http://damian-desktop:12345/\"%s\" -O/dev/null" % (temp) 
	os.system(data_package)

#tutaj jest to calkiem ladnie opisane: http://www.stealthcopter.com/blog/2010/02/python-interfacing-with-an-arduino/
