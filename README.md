# GardenForce-Demo
A new product based on IoTForce. 
The prototype is based on low-cost hardware to monitor the moisture in the soil and irrigate the plant based on a 5v motor that pumps the water. The moisture can be configured through Salesforce and the lectures from the sensor can be monitored. The intention is to create a centralized hub with an ESP32 in order to monitor multiple plants, and all the data can be reported or monitor in Salesforce.

The stack selected:
* Features in Salesforce:
    * Online monitoring of moisture.
    * Moisture level configuration for trigger the water pumping.
* IOT Proxy:
    * Ioticos(MQTT)
*  Hardware:
    * ESP32
    * Moisture sensor 
    * 5v Relay
    * 5v motor
* Software:         
    * Arduino IDE
    * Salesforce:
         * Custom Object: Plant
