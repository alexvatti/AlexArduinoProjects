'''
we will learn how to use the UART serial of ESP32 in MicroPython.

read the data from uart:
on -  command - turn on in built led
off - command - turn off in built led
rest of the data - Invalid
'''

from machine import UART,Pin
from time import sleep
led = Pin(2,Pin.OUT)

uart = UART(2,115200)
print(uart)

strmsg = " "
while True:
    if uart.any() > 0:
        strmsg = uart.read()
        print(strmsg)
        if 'on' in strmsg:
            uart.write("Turning on led\r\n")
            print("Turning on led")
            led.on()
        elif 'off' in strmsg:
            uart.write("Turning off led\r\n")
            print("Turning off led")
            led.off()
        elif '\r' in strmsg:
            continue
        else:
            uart.write("Invalid Command\r\n")
            print("Invalid command")
