import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import datetime as dt

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []
ser = serial.Serial()


# This function is called periodically from FuncAnimation
def animate(i, x, y):
    # Create figure for plotting

    # Read temperature (Celsius) from TMP102
    movement = read_serial()

    # Add x and y to lists
    x.append(dt.datetime.now().strftime('%H:%M:%S'))
    y.append(movement)

    # Limit x and y lists to 20 items
    x = x[-20:]
    y = y[-20:]

    # Draw x and y lists
    ax.clear()
    ax.plot(x, y)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('Movement over Time')
    plt.ylabel('Movement')


def connect_serial():
    port_name = input('enter serial port name')
    ser.port = port_name
    ser.baudrate = 9600
    print(ser.name)
    ser.write(b'hello')
    ser.close()


def read_serial():
    return np.random.uniform(0, 5)


if __name__ == '__main__':
    ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1000)
    plt.show()