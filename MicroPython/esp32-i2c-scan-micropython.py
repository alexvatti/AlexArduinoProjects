
from machine import Pin,SoftI2C

SDA_PIN=Pin(21)  #for ESP32
SCL_PIN=Pin(22)

i2c = SoftI2C(sda=SDA_PIN, scl=SCL_PIN, freq=10000)   

devices = i2c.scan()
if len(devices) == 0:
 print("No i2c device !")
else:
 print('i2c devices found:',len(devices))
 
for device in devices:
 print("At address: ",hex(device))
