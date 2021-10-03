#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <PubSubClient.h>
#include <WebServer.h>
#include "GardenForce_consts.h"

const String plantId = "PLANT_1";


WiFiClient mqttIPClientWifi;
PubSubClient mqttIPClient( mqttIPClientWifi );

typedef struct shoot_on_demand {
  bool shoot;
  String deviceId;
};
shoot_on_demand esp_now_data;

volatile int moistValue = 3200;

TaskHandle_t taskSendStatus;


void mqttCallback(char* topic, byte* payload, unsigned int length);
void mqttReconnect();

void mqttReconnect() {

  while (!mqttIPClient.connected()) {
    Serial.print("Intentando conexión Mqtt...");
    // Creamos un cliente ID
    String clientId = "IOTICOS_H_W_";
    clientId += String(random(0xffff), HEX);
    // Intentamos conectar
    if (mqttIPClient.connect(clientId.c_str(),mqtt_ip_user,mqtt_ip_password)) {
      Serial.println("Conectado!");
      // Nos suscribimos
      if(mqttIPClient.subscribe(mqtt_ip_topic_subscribe)){
        Serial.println("Suscripcion ok");
      }else{
        Serial.println("fallo Suscripciión");
      }
    } else {
      Serial.print("falló :( con error -> ");
      Serial.print(mqttIPClient.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");
      delay(MQTT_RETRYMS);
    }
  }
}

// https://stackoverflow.com/questions/9072320/split-string-into-string-array
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


void mqttCallback(char* topic, byte* payload, unsigned int length){
  String incoming = "";
  Serial.print("Mensaje recibido desde -> ");
  Serial.print(topic);
  Serial.println("");
  for (int i = 0; i < length; i++) {
    incoming += (char)payload[i];
  }
  incoming.trim();
  Serial.println("Mensaje -> " + incoming); 

  if (getValue(incoming,';',0) == plantId && getValue(incoming,';',3) == "MQTT"){
    Serial.println("New valid message");
    if (getValue(incoming,';',2).toInt() > 0){
       String parameter = getValue(incoming,';',1);
       if (parameter == "moist"){
          moistValue = getValue(incoming,';',2).toInt();
       }
       if (parameter == "read_ms")
          readMs = getValue(incoming,';',2).toInt();
       if (parameter == "flow_ms"){
          flowMS = getValue(incoming,';',2).toInt();
          defaultFlowMS = flowMS;
       }
    }else{
      String parameter = getValue(incoming,';',1);
      Serial.println(parameter);
      if (parameter == "hidrate"){
            Serial.println("hidrate");
            handle_hidrate();
            delay(flowMS);
      }
    }
    //espRequestScreenshotToCam();
  }
}

void bootUp(){
  plantId.toCharArray(msg,plantId.length()+1);
  if (!mqttIPClient.connected()) {
      mqttReconnect();
   }
  Serial.println("Connecting to mqtt");
  mqttIPClient.publish(mqtt_ip_topic_subscribe,msg);
}

void taskSendStatusMethod( void * parameter) {
  String statusMsg;
  for(;;) {
    mqttLoop();
    
    if (sensorStatus > 0){
      statusMsg = plantId+";"+String(sensorStatus);
      statusMsg.toCharArray(msg,statusMsg.length()+1);
      mqttIPClient.publish(mqtt_ip_topic_subscribe,msg);
      delay(readMs);      
    } else {
      delay(300);
    }
  }
}

// it wil set the static IP address to 192, 168, 10, 47
IPAddress local_IP(192, 168, 1, 135);
//it wil set the gateway static IP address to 192, 168, 2,2
IPAddress gateway(192, 168, 1 ,1);

// Following three settings are optional
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); 
IPAddress secondaryDNS(8, 8, 4, 4);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  pinMode(MOIST_SENSOR,INPUT);
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY, 1); // Disable by default
  
  Serial.println("The device started, now you can pair it with bluetooth!");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("SensorForce Ready!");
  Serial.println(WiFi.macAddress());
  Serial.print(WiFi.localIP());

  mqttIPClient.setServer(mqtt_ip, mqtt_ip_port);
  mqttIPClient.setCallback(mqttCallback);
  bootUp();

  xTaskCreatePinnedToCore(
      taskSendStatusMethod, 
      "taskSendStatus", 
      10000,  
      NULL,  
      0,  
      &taskSendStatus,  
      0);
 //Blynk.begin(blynk_auth, ssid, password);
}

void mqttLoop(){
  if (!mqttIPClient.connected()) {
      mqttReconnect();
   }  
   mqttIPClient.loop();
}

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
void handle_hidrate(void)
{
  digitalWrite(RELAY, 0);
  delay(flowMS);
  // 1 minuto - flowMS parado
  digitalWrite(RELAY,1);
}



void loop() {
  //
  mqttLoop();
  sensorStatus = analogRead(MOIST_SENSOR);
}
