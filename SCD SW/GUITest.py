import serial 
import time
import sys
from Tkinter import *


# for time calculations
temp = "0"
name = ''

# serial for linux
ser = serial.Serial("/dev/ttyACM0", baudrate=115200, timeout=0)

# enables gui window
master = Tk()
master.wm_title("title goes here")

# make a entry box 
log = Entry(master, width=50, takefocus=0)
log.pack()

# store textfield to variable 'name'
def saveName():
	global name
	name = log.get()

# save data to a file using 'name'
def printText():
	global t_end, temp, name, ser, f, startTime, time, master
	# find the time when button call started
	startTime = time.time()
	# find the time for how long the duration of the test
	t_end = time.time() + 5

	# calculate percent complete (not working yet)
	percentComplete = time.time() / t_end
	f = open(name,'a')
	print('start recording serial')

	# 5 sec loop of writing serial to file 'name'
	update_progress(0)
	while time.time() < t_end:
		temp = ser.read()
		while (temp != "\n") and (temp != "\r"):
			f.write(temp)
			temp = ser.read()
		if temp == "\n":
			f.write(",")
			f.write("%s\n" % (time.time() - startTime))
	print('done recording serial')
	update_progress(100)
	sys.exit()

def update_progress(progress):
    print '\r[{0}] {1}%'.format('#'*(progress/10), progress)


# create button 
B = Button(master, text="Set Save Name", width=11, command=saveName)
B.pack(side=RIGHT)
C = Button(master, text="Run Test", width=11, command=printText)
C.pack(side=LEFT)

mainloop()
log.Entry(master, width=50)
log.pack()