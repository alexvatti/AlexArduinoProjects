'''
The HC-SR04 ultrasonic sensor uses sonar to determine the distance to an object.
This sensor reads from 2cm to 400cm (0.8inch to 157inch) with an accuracy of 0.3cm (0.1inches),
which is good for most hobbyist projects.
'''

from hcsr04 import HCSR04
from time import sleep

# ESP32
sensor = HCSR04(trigger_pin=13, echo_pin=12, echo_timeout_us=10000)


while True:
    distance = sensor.distance_cm()
    if (distance > 0):
        print('Distance:', distance, 'cm')
    sleep(1)
