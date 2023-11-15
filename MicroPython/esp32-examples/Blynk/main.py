import Blynklib as blynklib

import network
import utime as time
from machine import Pin
import dht


WIFI_SSID = "TP-Link_375D"
WIFI_PASS = "11862574"
# Connect to Blynk server
BLYNK_AUTH_TOKEN =  "mUPRPJItPUzRaeJIMgS2ShNeT-E3F_1M"


def do_connect():
    print("Connecting to WiFi network ")
    sta = network.WLAN(network.STA_IF)
    sta.active(True)
    sta.connect(WIFI_SSID, WIFI_PASS)
    while not sta.isconnected():
        time.sleep(1)
        print('WiFi connect retry ...')

    print('WiFi IP:', sta.ifconfig())
    print("Wi-Fi connected:", sta.ifconfig())


sensor = dht.DHT11(Pin(15))
do_connect()
print("Connecting to Blynk server...")
blynk = blynklib.Blynk(BLYNK_AUTH_TOKEN)


# Define pin numbers
led_pin = 2

# Initialize LED pin
led = Pin(led_pin, Pin.OUT)

# Define Blynk virtual pin handlers
@blynk.on("V0")
def v0_handler(value):
    if int(value[0]) == 1:
        led.value(1)
    else:
        led.value(0)



def dht_temp():
    sensor.measure()
    temp = sensor.temperature()
    blynk.virtual_write(1,temp)


while True:
    blynk.run()
    dht_temp()
