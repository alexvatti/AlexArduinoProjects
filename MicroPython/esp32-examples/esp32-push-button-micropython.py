'''
Read a push button switch and control an LED based on the switch state with an ESP32 using MicroPython: 
A code example for reading a button's state and toggling an LED on or off according to the button's input.
'''

from machine import Pin
from time import sleep
print("Hello World\n")
red_led = Pin(2,Pin.OUT)
button = Pin(5, Pin.IN)

while(True):
    if ( button.value() == 1) :
        red_led.value(True)
        sleep(1)
    else:
        red_led.value(False)
        sleep(1)
