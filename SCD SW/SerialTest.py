import serial 
import time

ser = serial.Serial()
ser.baudrate = 115200
ser.port = '/dev/ttyACM0'
ser.open()
f = open('testData.csv','a')
t_end = time.time() + 5

while time.time()< t_end:
	f.write(ser.read())
	f.write(",/n")
	f.close()
	f = open('testData.csv','a')
