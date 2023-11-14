'''
Realy Exercise
'''
from machine import Pin
from time import sleep

relay_control = Pin(4, Pin.OUT)

while True:
    relay_control.value(1)
    sleep(5)
    relay_control.value(0)
    sleep(5) 
