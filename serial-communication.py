import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import datetime as dt
import time
import pandas as pd
import datetime

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []
ser = serial.Serial()
start_time = 0
pause = False


# This function is called periodically from FuncAnimation
def animate(i, x, y, end_time):
    # Create figure for plotting
    global pause
    movement = read_serial()

    if time.time() > end_time:
        ser.write(b'\x01')
        if not pause:
            total_minutes = read_serial() * 5
            total_sleep = [0 for _ in xs]
            total_sleep[0] = total_minutes
            df = pd.DataFrame({
                'time': [x.strftime("%Y-%m-%d %H:%M:%S") for x in xs],
                'movement': ys,
                'total sleep': total_sleep
            })
            df.to_excel('sleep_data_' + xs[0].strftime("%Y-%m-%d_%H:%M:%S") + '.xlsx')
            end = 6000 # this corresponds to 10 minutes
            start = 0
            minimum = 100000000
            minindex = 0
            maxindex = 0
            maximum = -1
            offset = 1
            if len(xs) >= 6000:
                print('You slept for less than 10 minutes, '
                      'so your least and most restful sleep period will be identical.')
                offset = 6000

            for i in range(len(xs)//200):
                summed = sum(ys[start:end])
                if summed < minimum:
                    minimum = summed
                    minindex = start
                if summed > maximum:
                    maximum = summed
                    maxindex = start

                start = end
                end = end + 6000

            print(('Your most restful (10 min) period was: ' + xs[minindex].strftime('%Y-%m-%d %H:%M:%S')) + ' to ' +
                  xs[minindex + offset-1].strftime("%Y-%m-%d %H:%M:%S"))
            print(('Your least restful (10 min) period was: ' + xs[maxindex].strftime('%Y-%m-%d %H:%M:%S')) + ' to ' +
                  xs[maxindex + offset-1].strftime("%Y-%m-%d %H:%M:%S"))
        pause = True

    else:
        ser.write(b'\x00')
        if movement is not None:
            # Add x and y to lists
            x.append(dt.datetime.now())
            y.append(movement)

            # Draw x and y lists
            ax.clear()
            ax.plot(x, y)

            # Format plot
            plt.xticks(rotation=45, ha='right')
            plt.subplots_adjust(bottom=0.30)
            plt.title('Movement over Time')
            plt.ylabel('Movement')
        else:
            print('No movement read from UART')


def connect_serial():
    port_name = 'COM4'
    ser.port = port_name
    ser.baudrate = 9600
    ser.timeout = 1
    ser.open()


def read_serial():
    return np.random.uniform(0, 150)


def get_end_time():
    hours = float(input('How many hours would you like to sleep for? '))
    start_time = time.time()
    end_time = hours * 60 * 60 + start_time
    return end_time


if __name__ == '__main__':
    end_time = get_end_time()
    connect_serial()
    ax.get_yaxis().set_visible(False)
    ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys, end_time), interval=100)
    plt.show()

