#!/usr/bin/python3
import sys, os
sys.path.append('/rest /var/www/html/GardenForce-Demo/python/')
import mqtt_proxy
client = mqtt_proxy.connect_mqtt()
client.loop_forever()