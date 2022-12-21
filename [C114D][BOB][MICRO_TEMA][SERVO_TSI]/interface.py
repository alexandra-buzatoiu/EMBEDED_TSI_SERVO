from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import tkinter as tk
import numpy as np
import serial as sr
#from serial import Serial

data = np.array([])
cond = False

# plot data


def plot_data():
    global cond, data

    if (cond == True):
        a = s.readline()
        a.decode()
        print(a)

        data=np.append(data,float(a))
        lines.set_xdata(np.arange(0, len(data)))
        lines.set_ydata(data)

        canvas.draw()
    root.after(250, plot_data)


def plot_start():
    global cond
    cond = True
    s.reset_input_buffer()


def plot_stop():
    global cond
    cond = False


root = tk.Tk()
root.title('Real Time Plot')
root.configure(background='light green')
root.geometry("600x465")

# Create Plot

fig = Figure()
ax = fig.add_subplot(111)

ax.set_title('Serial Data')
ax.set_xlabel('Timp')
ax.set_ylabel('Intensitate')
ax.set_xlim(0, 200)
ax.set_ylim(0, 400)
lines = ax.plot([], [])[0]

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().place(x=10, y=10, width=500, height=400)
canvas.draw()

# Create utton
root.update()
start = tk.Button(root, text="Start", font=(
    'Times New Roman', 12), command=lambda: plot_start())
start.place(x=200, y=425)

root.update()
stop = tk.Button(root, text="Stop", font=(
    'Times New Roman', 12), command=lambda: plot_stop())
stop.place(x=start.winfo_x() + start.winfo_reqwidth() + 20, y=425)

# Serial Port
s = sr.Serial('COM9', 115200)

if s.isOpen():
    print(s.name + ' is open...')

s.reset_input_buffer()

root.after(1, plot_data)
root.mainloop()