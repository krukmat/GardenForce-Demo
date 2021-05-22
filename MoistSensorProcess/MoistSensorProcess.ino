#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <PubSubClient.h>
#include <esp_now.h>


const String plantId = "PLANT_1";
const char* ssid = "MIWIFI_5G_2jJ5_EXT";
const char* password = "xvFYmqRv";

WiFiClient mqttIPClientWifi;
PubSubClient mqttIPClient( mqttIPClientWifi );
const char* mqtt_ip = "ioticos.org";
const int mqtt_ip_port = 1883;
const char* mqtt_ip_user = "d2uNYOZq2J5uL3T";
const char* mqtt_ip_password = "DwqGBXa7LuVlgBG";
const char *mqtt_ip_topic = "HPIbCG0C72lcw6g/output";
const char *mqtt_ip_topic_subscribe = "HPIbCG0C72lcw6g/input";
char auth[] = "_Hk2RUSUh4uTDaL4468L7rrmxcds3rYn"; 
char msg[12];
int moistValue = 3200;
int sensorStatus = 0;

// 10:52:1C:62:DB:60
uint8_t broadcastAddress[] = {0x10, 0x52, 0x1C, 0x62, 0xDB, 0x60};
typedef struct shoot_on_demand {
  bool shoot;
  String deviceId;
};
shoot_on_demand esp_now_data;

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
      delay(5000);
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

void espRequestScreenshotToCam(){
  esp_now_data.shoot = true;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &esp_now_data, sizeof(esp_now_data));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
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

  if (getValue(incoming,';',0) == plantId && getValue(incoming,';',2) == "MQTT"){
    if (getValue(incoming,';',1).toInt() > 0)
        moistValue = getValue(incoming,';',1).toInt();    
    espRequestScreenshotToCam();
  }
}

void bootUp(){
  plantId.toCharArray(msg,plantId.length()+1);
  if (!mqttIPClient.connected()) {
      mqttReconnect();
   }
  mqttIPClient.publish(mqtt_ip_topic_subscribe,msg);
}

void taskSendStatusMethod( void * parameter) {
  String statusMsg;
  for(;;) {
    mqttLoop();
    statusMsg = plantId+";"+String(sensorStatus);
    statusMsg.toCharArray(msg,statusMsg.length()+1);
    mqttIPClient.publish(mqtt_ip_topic_subscribe,msg);
    delay(60000);
  }
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(34,INPUT);
  pinMode(14,OUTPUT);
  digitalWrite(14, 1); // Disable by default
  
  Serial.println("The device started, now you can pair it with bluetooth!");
  WiFi.mode(WIFI_AP_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  
  //Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
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
      taskSendStatusMethod, /* Function to implement the task */
      "taskSendStatus", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &taskSendStatus,  /* Task handle. */
      0); /* Core where the task should run */
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
  sensorStatus = analogRead(34);
  // TODO: Si el valor es  == 4095 => Mandar 1 sino 0
  if (sensorStatus >= moistValue){
    digitalWrite(14, 0);
  } else {
    digitalWrite(14, 1);
  }
  //Serial.println(value);
  delay(100);
}
