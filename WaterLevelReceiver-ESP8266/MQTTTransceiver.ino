
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Trekkers_Hut";
const char* password = "Alcrai.Ace1992";
const char* mqtt_server = "raspberrypi.local";
int server_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
int msg = 0;
int value = 0;

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print(topic);
  String message;
  
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print(":");
  Serial.println(message);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    String clientId = "ESPClient8266";
      clientId += String(random(0xffff), HEX);

  WiFi.mode(WIFI_STA);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("topics/startup", "starting");
      bool status = client.subscribe("topics/seton");
      Serial.print("subscribed:");
      Serial.println(status);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void mqtt_setup() {
  setup_wifi();
  client.setServer(mqtt_server, server_port);
  client.setCallback(callback);
}

void mqtt_loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}