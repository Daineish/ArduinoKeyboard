#!/usr/bin/python3

from time import sleep
import serial

print("Setting up arduino...")
# arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)
arduino = serial.Serial(port='/dev/cu.usbmodem14301', baudrate=115200, timeout=.1)
print("Complete.")

def readArduino():
    return arduino.readline().decode().strip()

while True:
    # Try reading from Arduino
    value = readArduino()

    if(value):
        # TODO: strip final 01 for now
        print(value[:-2])

    # sleep
    sleep(0.05)
