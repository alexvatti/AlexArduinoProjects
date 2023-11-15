import network
import time
from umqtt.simple import MQTTClient
from machine import Pin

import gc
gc.collect()

WIFI_SSID = "TP-Link_375D"
WIFI_PASS = "11862574"

SERVER = "mqtt-v2-thingspeak.com"
PORT=1883
CHANNEL_ID = ""
USER=""
CLIENT_ID=""
PASSWORD=""


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

do_connect()
client = MQTTClient(CLIENT_ID,SERVER, PORT,USER,PASSWORD)
client.connect()

print("MQTT Connected")

counter = 0
topicOut = "channels/" + CHANNEL_ID + "/publish"

while True:
    if counter > 100:
	counter = 0
    client.publish(topicOut,"filed1="+str(counter))
    print(counter)
    counter = counter +  10
    time.sleep(2)
