#ifndef WiFiHandler
#define WiFiHandler
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

void setup_wifi();

void wifi_connect();

String getWiFiPass();

String getWiFiSSID();

void saveParamsCallback();
#endif