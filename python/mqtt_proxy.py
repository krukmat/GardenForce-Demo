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
    plant_id = data
    
    #TODO: Leer PlantID
    # TODO: Hacer SOQL a Salesforce para obtener el dato de Moist
    # TODO: Publish el dato para que lo lea el dispositivo
    #try:
    #    result = sf.sobjects.Sensor__c.insert({'Date__c': data['created_at'], 'External_id__c': data['entry_id'], 'value__c':  data['field1'], 
    #                                           'channel__c': data['channel_id']})
    #catch:
    #    pass
    #print(result)        
 
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set(username="d2uNYOZq2J5uL3T", password="DwqGBXa7LuVlgBG")
client.connect("ioticos.org", 1883, 60)
client.loop_forever()