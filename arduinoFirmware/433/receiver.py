import serial
import os

try:
	arduino = serial.Serial('/dev/ttyACM0', 9600)
except:
	print("Failed to connect on /dev/ttyACM0" )

print("Starting 'drone' application")

while 1:
	temp = arduino.readline()
	print(temp)

