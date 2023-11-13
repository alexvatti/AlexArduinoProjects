'''
 servo motor from the ESP32 with a Python script
 '''
from machine import Pin, PWM
from time import sleep

frequency = 50
servo = PWM(Pin(13), frequency)

while True:
  #servo motor angle 0 to 180
  for duty_cycle in range(0, 123,10):
    servo.duty(duty_cycle)
    sleep(1)
    
  for duty_cycle in range(123, -1, -10):
    servo.duty(duty_cycle)
    sleep(1)
