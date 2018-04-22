import serial 
import time

ser = serial.Serial()
ser.baudrate = 115200
ser.port = '/dev/ttyACM0'
ser.open()
f = open('testData.csv','a')
t_end = time.time() + 5
temp = "0"

while time.time()< t_end:
	temp = ser.read()
	while (temp != "\n")|(temp != "\r"):
		f.write(temp)
		temp = ser.read()
	f.write(",")
	f.write("Trees\n")
	f.close()
	f = open('testData.csv','a')
