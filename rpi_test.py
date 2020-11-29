#!/usr/bin/env python3
import serial
from firebase import firebase
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.flush()
    firebase = firebase.FirebaseApplication('https://wildfire-robot.firebaseio.com/', None)

    while True:
       # ser.write(b"Hello from Raspberry Pi!\n")
        line = ser.readline().decode('utf-8').rstrip()
        direction = firebase.get('/wildfire-robot', 'data')    
        print(line)
        print("\n")
        ser.write(str(direction))
        
