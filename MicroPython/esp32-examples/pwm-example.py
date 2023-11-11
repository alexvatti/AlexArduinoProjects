'''
In MicroPython, control LED brightness on ESP32 by using PWM on
PIN 2 for LED intensity adjustment.
'''

from machine import Pin, PWM
from time import sleep

frequency = 5000
led = PWM(Pin(2), frequency)

while True:
  for duty_cycle in range(0, 1024,100):
    led.duty(duty_cycle)
    sleep(1)
