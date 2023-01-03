#ifndef MQTTTransceiver
#define MQTTTransceiver
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void mqtt_setup(void (*switchOn)(void), void (*switchOff)(void),char* server,int port);
void mqtt_loop();

#endif