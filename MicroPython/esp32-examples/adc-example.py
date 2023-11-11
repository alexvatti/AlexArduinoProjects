'''
Reading Analog Inputs with ESP32 using MicroPython
'''

'''
ADC.atten(ADC.ATTN_11DB) 
ADC.ATTN_0DB : the full range voltage: 0- 1.2V
ADC.ATTN_2_5DB : the full range voltage: 0- 1.5V
ADC.ATTN_6DB : the full range voltage: 0- 2.0V
ADC.ATTN_11DB : the full range voltage: 0-3.3V
'''
'''
ADC.width(bit)
ADC.WIDTH_9BIT: range 0-511
ADC.WIDTH_10BIT: range 0-1023
ADC.WIDTH_11BIT: range 0-2047
ADC.WIDTH_12BIT: range 0-4095
'''

from machine import Pin, ADC            #importing Pin and ADC class
from time import sleep                  #importing sleep class

potentiometer = ADC(Pin(15))              #creating potentiometer object
potentiometer.atten(ADC.ATTN_11DB)       #3.3V full range of voltage

while True:
 potentiometer_value = potentiometer.read()   #reading analog pin
 print("ADC Value =",potentiometer_value)                   #printing the ADC value
 sleep(1)
