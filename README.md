# GardenForce-Demo
A new product based on IoTForce. 
The prototype is based on low-cost hardware to monitor the moisture in the soil and irrigate the plant based on a 5v motor that pumps the water. The moisture can be configured through Salesforce and the lectures from the sensor can be monitored. The intention is to create a centralized hub with an ESP32 in order to monitor multiple plants, and all the data can be reported or monitor in Salesforce.

The stack selected:
* Features in Salesforce:
    * Online monitoring of moisture.
    * Moisture level configuration for trigger the water pumping.
    * Flow configuration (based on minutes)
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
## General Schema
![Schematics](https://github.com/krukmat/GardenForce-Demo/blob/159c5497d52ea9f4a9dd97e8ecaf703c78a2e915/images/GardenForce.jpeg)
##  Hardware
![Schematics](https://github.com/krukmat/GardenForce-Demo/blob/7f40088fdd00eb0f9112b119c42a06c2868b97db/images/version2.jpg)
![Schematics](https://github.com/krukmat/GardenForce-Demo/blob/7f40088fdd00eb0f9112b119c42a06c2868b97db/images/version2_internal.jpg)

## Salesforce
![Config](https://github.com/krukmat/GardenForce-Demo/blob/59f1f45d0b90cbab48707d1845b6b19c51e80a89/images/screenshot_sf.png)
![History](https://github.com/krukmat/GardenForce-Demo/blob/dab6476364e0883ef06dd59ba2e45e5e8e7263f6/images/salesforce-history.png)
![Report](https://github.com/krukmat/GardenForce-Demo/blob/e80d5873ee5d96a9f12610b9f7f7e4d635eeb690/images/report.png)

## Reload secuence
* (python folder) nohup python3 ./forever.py > gardenforce.log &
* systemctl reload apache2
* Review errors: 
       * cd /var/log/apache2/
       * cat access.log
       * cat error.log