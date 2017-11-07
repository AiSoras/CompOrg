import matplotlib.pyplot as plt
import math
from tkinter import *

pi = 3.1415

x = [(i*pi/2)/100 for i in range(300,3700)]
y = [math.cos(i/2)**2+math.sqrt(i) for i in x]

window = Tk()

t = "Макс значение функции на интервале: {}".format(max(y))
l = Label(window, text=t)
l.pack()

window.geometry("500x500")

mainloop()

plt.plot(x,y)
plt.ylabel('cos^2(x/2)+sqrt(x)')
plt.show()