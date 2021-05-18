#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <PubSubClient.h>


const String plantId = "PLANT_1";
const char* ssid = "MIWIFI_5G_2jJ5_EXT";
const char* password = "xvFYmqRv";

WiFiClient mqttIPClientWifi;
PubSubClient mqttIPClient( mqttIPClientWifi );
const char* mqtt_ip = "ioticos.org";
const int mqtt_ip_port = 1883;
const char* mqtt_ip_user = "hGR2rL1latTuCnB";
const char* mqtt_ip_password = "ASJ5c61zVvtuib7";
const char *mqtt_ip_topic = "htO9wfUxA50uzDS/output";
const char *mqtt_ip_topic_subscribe = "htO9wfUxA50uzDS/input";
char auth[] = "_Hk2RUSUh4uTDaL4468L7rrmxcds3rYn"; 
char msg[12];
int moistValue = 3200;

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
      delay(5000);
    }
  }
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
  moistValue = incoming.toInt();
}

void bootUp(){
  plantId.toCharArray(msg,plantId.length());
  if (!mqttIPClient.connected()) {
      mqttReconnect();
   }
  mqttIPClient.publish(mqtt_ip_topic,msg);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(34,INPUT);
  pinMode(14,OUTPUT);
  digitalWrite(14, 1); // Disable by default
  
  Serial.println("The device started, now you can pair it with bluetooth!");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("SensorForce Ready!");
  Serial.print(WiFi.localIP());

  mqttIPClient.setServer(mqtt_ip, mqtt_ip_port);
  mqttIPClient.setCallback(mqttCallback);
  bootUp();
}

void mqttLoop(){
  if (!mqttIPClient.connected()) {
      mqttReconnect();
   }  
   mqttIPClient.loop();
}

void loop() {
  mqttLoop();
  // put your main code here, to run repeatedly:
  int value = analogRead(34);
  // TODO: Si el valor es  == 4095 => Mandar 1 sino 0
  if (value >= moistValue){
    digitalWrite(14, 0);
  } else {
    digitalWrite(14, 1);
  }
  //Serial.println(value);
  delay(100);
}
