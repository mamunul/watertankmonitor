#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
WiFiManager wm;
WiFiManagerParameter custom_mqtt_server("server", "mqtt server", "", 40);
WiFiManagerParameter custom_mqtt_port("port", "mqtt port", "1883", 10);
WiFiManagerParameter custom_mqtt_key("key", "mqtt client id", "", 10);

void setup_wifi() {
  WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP
  // put your setup code here, to run once:
  //reset settings - wipe credentials for testing
  wm.resetSettings();
  wm.addParameter(&custom_mqtt_server);
  wm.addParameter(&custom_mqtt_port);
  wm.addParameter(&custom_mqtt_key);
  wm.setConfigPortalBlocking(false);
  wm.setSaveParamsCallback(saveParamsCallback);
  //automatically connect using saved credentials if they exist
  //If connection fails it starts an access point with the specified name
  if (wm.autoConnect("AutoConnectAP")) {
    Serial.println("connected...yeey :)");
  } else {
    Serial.println("Configportal running");
  }
}

void wifi_connect() {
  wm.process();
}

String getWiFiPass() {
  return wm.getWiFiPass();
}

String getWiFiSSID() {
  return wm.getWiFiSSID();
}

void saveParamsCallback() {

}