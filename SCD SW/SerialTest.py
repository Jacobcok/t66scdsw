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
	while (temp != "\n") and (temp != "\r"):
		f.write(temp)
		temp = ser.read()
	if temp == "\n":
		f.write(",")
		f.write("%d\n" % (t_end-time.time))
	f.close()
	f = open('testData.csv','a')
