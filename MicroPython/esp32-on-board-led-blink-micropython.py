'''
Blink the onboard LED on an ESP32 using MicroPython: 
A simple code example to toggle the built-in LED on and off in MicroPython on an ESP32 board.
'''

from machine import Pin
from time import sleep

print("Hello World - ESP32 - LED -BLINK\n")
on_board_led = Pin(2,Pin.OUT)

while True:
    on_board_led.value(1)
    sleep(1)
    on_board_led.value(0)
    sleep(1)
