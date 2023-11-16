'''
ESP32 MicroPython: External Interrupt
switch connected to Pin 15
tested/handler on in build led pin 2 -toggling
'''

import machine
from machine import Pin


led = Pin(2,Pin.OUT)
sw = Pin(15,Pin.IN)

def interrupt_handler(pin):
    led.value(not led.value())

#Push button switch - by defauly - pulled up - high
sw.irq(trigger=Pin.IRQ_FALLING,handler=interrupt_handler)

#touch button switch - by default - pulled down - low
#sw.irq(trigger=Pin.IRQ_RISING,handler=interrupt_handler)
