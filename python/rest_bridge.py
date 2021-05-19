#!/usr/bin/python3
import sys, os
sys.path.append('/root/GardenForce-Demo/python')
from flask import Flask
import mqtt_proxy
app = Flask(__name__)

@app.route('/setup')
def index():
    message = request.args.get('moist', '')
    if message:
        client = mqtt_proxy.connect_mqtt()
        mqtt_proxy.mqtt_publish(client, message)
    return 'OK'
    