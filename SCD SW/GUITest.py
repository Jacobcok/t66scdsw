# import serial 
import time
from Tkinter import *

# serial for windows
# ser = serial.Serial("/dev/ttyUSB0", baudrate=9600, timeout=0)

## serial for linux
# ser = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=0)

# enables gui window
master = Tk()
# log = Entry(master)
# log.pack()
# log.focus_set()
master.wm_title("title goes here")

# make a entry box 
log = Entry(master, width=30, takefocus=0)
log.pack()

def callback():
	text = log.get()

def calltest():
	print log.get()
	
# create button 
B = Button(master, text="save name", width=11, command=callback)
B.pack(side=RIGHT)
C = Button(master, text="print text", width=11, command=calltest)
C.pack(side=RIGHT)

mainloop()
log.Entry(master, width=50)
log.pack()
f = open(text,'a')


# ser.open()
# f = open('testData.csv','a')
# t_end = time.time() + 5


# while time.time() < t_end:
	# f.write(ser.read())
	# f.close()
	# f = open('testData.csv','a')