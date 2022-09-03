#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* mqtt_server = "raspberrypi.local";
int server_port = 1883;
bool forcedSwitchOn = false;
WiFiClient espClient;
PubSubClient mqtt_client(espClient);
unsigned long lastMsg = 0;
int msg = 0;
int value = 0;

char* switchTopic = "topics/seton";
char* onlineTopic = "topics/online";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print(topic);
  String message;

  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print(":");
  Serial.println(message);
  if (message.equals("on")) {
    forcedSwitchOn = true;
    Serial.println("forcedSwitchOn");
    switchOn();
  } else {
    Serial.println("forcedSwitchOff");
    switchOff();
  }
}

void reconnect() {
  while (!mqtt_client.connected()) {
    Serial.println("Attempting MQTT connection...");
    String clientId = "ESPClient8266";
    clientId += String(random(0xffff), HEX);

    WiFi.mode(WIFI_STA);
    if (mqtt_client.connect(clientId.c_str())) {
      Serial.println("connected");
      mqtt_client.publish(onlineTopic, "true");
      bool status = mqtt_client.subscribe(switchTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      delay(5000);
    }
  }
}

void mqtt_setup() {
  mqtt_client.setServer(mqtt_server, server_port);
  mqtt_client.setCallback(callback);
}

void mqtt_loop() {
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop();
}