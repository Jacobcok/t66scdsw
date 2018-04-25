import serial 
import time

startTime = time.time()
ser = serial.Serial()
ser.baudrate = 9600
ser.port = '/dev/ttyACM0'
ser.open()
f = open('testData.csv','a')
t_end = time.time() + 20
temp = "0"

while time.time()< t_end:
	temp = ser.read()
	while (temp != "\n") and (temp != "\r"):
		f.write(temp)
		temp = ser.read()
	if temp == "\n":
		f.write(",")
		f.write("\n")
		#f.write("%s\n" % (time.time() - startTime))
#	f.close()
#	f = open('testData.csv','a')
