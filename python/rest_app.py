#!/usr/bin/python3
import sys, os
sys.path.append('/rest /var/www/html/GardenForce-Demo/python/')
from flask import Flask, request
import mqtt_proxy
app = Flask(__name__)

@app.route('/setup')
def index():
    value = request.args.get('moist', '')
    plantid = request.args.get('plant_id')
    message = plantid + ";" + value + ";MQTT"
    if value and plantid:
        client = mqtt_proxy.connect_mqtt()
        mqtt_proxy.mqtt_publish(client, message)
    return 'OK'
    