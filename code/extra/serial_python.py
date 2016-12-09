import sys, serial
from serial.tools import list_ports

def getTeensyPort():
    for port in list(list_ports.comports()):
        if port[2].find("VID:PID=2341:0043") >= 0:
            return port[0]

ser = serial.Serial(getTeensyPort(), 9600)


def clear():
    for i in range(16):
        if i > 0:
            ser.write(str(i) + ",0\n")


def loo():            
    while True:
        for i in range(16):
            if i > 0:
                ser.write(str(i-1) + ",0\n")
            else:
                ser.write(str(16-1) + ",0\n")
            ser.write(str(i) + ",1\n")
            time.sleep(0.02)
