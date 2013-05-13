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
	data_package="wget http://localhost:12345/\"%s\" -O/dev/null" % (temp) 
	os.system(data_package)

#Kudos: http://www.stealthcopter.com/blog/2010/02/python-interfacing-with-an-arduino/
