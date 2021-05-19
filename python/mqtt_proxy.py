#!/usr/bin/python3
import paho.mqtt.client as mqtt
from salesforce_api import Salesforce
import json

sf = Salesforce(username='matias@kforce.com', password='6tgAwEYL6Vj6UDS', security_token='qy5IOYAOupD2lmO3jXCJs52N7')

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("HPIbCG0C72lcw6g/input")

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    data = msg.payload
    data = data.decode('utf8').replace("'", '"')
    print(data)
    # Evitar el loopback de MQTT
    if  ";MQTT" in data == False:
        #TODO: Caso donde se envia PlantId;valor de humedad
        if ";" in data:
            parameters = data.split(";")
            result = sf.sobjects.Plant__c.upsert("PlantId__c", parameters[0], {"current__c": parameters[1]})
        else:
            # Caso que se recibe desde el ESP-32 para que se devuelva el valor desde SF
            if "PLANT" in data:
                plant_id = data
                try:
                    result = sf.sobjects.query("SELECT moist__c FROM Plant__c WHERE PlantId__c = '"+plant_id+"'")
                    moist = int(result[0]['moist__c'])
                    print(moist)
                    message = plant_id + ";"+ str(moist) + ";MQTT"
                    client.publish("HPIbCG0C72lcw6g/input", moist)
                except:
                    print("Error")

def mqtt_publish(client, message):
    client.publish("HPIbCG0C72lcw6g/input", message)

def connect_mqtt():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.username_pw_set(username="d2uNYOZq2J5uL3T", password="DwqGBXa7LuVlgBG")
    client.connect("ioticos.org", 1883, 60)
    return client
