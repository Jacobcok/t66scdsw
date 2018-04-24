from Tkinter import *

master = Tk()

e = Entry(master)
e.pack()

e.focus_set()

def callback():
    print e.get()

b = Button(master, text="get", width=10, command=callback)
b.pack(side=RIGHT)

mainloop()
e = Entry(master, width=50)
e.pack()

text = e.get()