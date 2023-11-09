'''
Blink an RGB LED connected to an ESP32 using MicroPython: 
Demonstrates how to control and blink an RGB LED connected via a daughter board on an ESP32 using MicroPython
'''

from machine import Pin
from time import sleep
print("Hello World - ESP32 - RGB -LEDS \n")
red_led = Pin(2,Pin.OUT)
green_led = Pin(5,Pin.OUT)
blue_led = Pin(23,Pin.OUT)

while(True):
    red_led.value(1)
    sleep(1)
    red_led.value(0)
    sleep(1)
    green_led.value(1)
    sleep(1)
    green_led.value(0)
    sleep(1)
    blue_led.value(1)
    sleep(1)
    blue_led.value(0)
    sleep(1)
