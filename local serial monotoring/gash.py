from serial.tools import list_ports
from datetime import datetime

import serial
import time
import csv

ports = list_ports.comports()
for port in ports:
    print(port)

f = open("data2.csv", "a", newline='')
f.truncate()

SERIAL_PORT = 'com'+input()
SERIAL_BAUD = 9600
serialCom = serial.Serial(SERIAL_PORT, SERIAL_BAUD)

serialCom.setDTR(False)
time.sleep
serialCom.flushInput()
serialCom.setDTR(True)


try:
    k = False
    while True:
        # try:
        s_byte = serialCom.readline()
        decoded_bytes = s_byte.decode("utf-8").strip()
        # print(s_byte)

        # parse line
        if k:
            values = ['Time', 'CO2', 'CO', 'NH4', 'Temperature', 'Humedity']

            print(values)

        else:
            now = datetime.now()
            time = [now.strftime("%d:%m:%y %H:%M:%S UTC")]
            values = [float(x) for x in decoded_bytes.split(',')]
            valuewithTime = time + values
            print(valuewithTime)
            # plt.cla()
            # plt.plot(values[0], values[1], label='Ro')
            # plt.plot(values[0], values[2], label='values')
            # plt.xlabel('Time')
            # plt.ylabel('Sensor Values')

        writer = csv.writer(f, delimiter=",")
        if k:

            writer.writerow(values)
            k = False
        else:
            writer.writerow(valuewithTime)
        # except:
        #     print("Error: line was not recorded")
except KeyboardInterrupt:
    f.close()
    serialCom.close()


# def on_close(event):
#     flag = False


# fig, ax = plt.subplots()
# fig.canvas.mpl_connect('close_event', on_close)

# ani = (FuncAnimation(fig, update_plot, interval=100))

# plt.show()
