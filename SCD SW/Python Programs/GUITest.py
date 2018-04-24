import serial 
import time
import sys
from Tkinter import *


# for time calculations
temp = "0"
name = ''

# serial for linux
ser = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=0)

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
	t_end = startTime + 5
	# file name, appending mode	
	f = open(name,'a')
	print('start recording serial')

	# loop of writing serial to file 'name'
	update_progress(0)
	while time.time() < t_end:

		# progress bar
		numer = int(100*(time.time() - startTime))
		denom = int(100*(t_end - startTime))
		percentComplete = 100*numer/denom	
		update_progress(percentComplete)

		temp = ser.read()
		# write serial to 'name' unless end of line or carridge return
		while (temp != "\n") and (temp != "\r"):
			f.write(temp)
			temp = ser.read()
		# if end of line append comma seperation and timestamp to 'name'
		if temp == "\n":
			f.write(",")
			f.write("%s\n" % (time.time() - startTime))
	update_progress(100)
	print('\ndone recording serial')

# proress bar. 0 < 'progress' < 100
def update_progress(progress):
    sys.stdout.write('\r Progress: {1}% [{0}{2}]'.format('#'*(progress/2), progress,'_'*(50-(progress/2))))
    sys.stdout.flush()


# create button 
B = Button(master, text="Set Save Name", width=11, command=saveName)
B.pack(side=RIGHT)
C = Button(master, text="Run Test", width=11, command=printText)
C.pack(side=LEFT)

mainloop()
log.Entry(master, width=50)
log.pack()