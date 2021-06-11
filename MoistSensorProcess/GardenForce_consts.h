const String plantId = "PLANT_1";
const char* ssid = "MIWIFI_5G_2jJ5_EXT";
const char* password = "xvFYmqRv";

const int MOIST_SENSOR = 34;
const int RELAY = 14;

const char* mqtt_ip = "ioticos.org";
const int mqtt_ip_port = 1883;
const char* mqtt_ip_user = "d2uNYOZq2J5uL3T";
const char* mqtt_ip_password = "DwqGBXa7LuVlgBG";
const char *mqtt_ip_topic = "HPIbCG0C72lcw6g/output";
const char *mqtt_ip_topic_subscribe = "HPIbCG0C72lcw6g/input";
const int MQTT_RETRYMS = 5000;

char auth[] = "_Hk2RUSUh4uTDaL4468L7rrmxcds3rYn"; 
char msg[12];
int moistValue = 3200;
int readMs = 180000;
int sensorStatus = 0;
// riego incremental. Caudal/min
int defaultFlowMS = 10000;
int flowMS = 10000;
int deltaMS = 60000;
float deltaPerc = 0.50;
int minDelta = 100;

// 10:52:1C:62:DB:60
uint8_t broadcastAddress[] = {0x10, 0x52, 0x1C, 0x62, 0xDB, 0x60};