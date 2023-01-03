#include "RF433Receiver.h"
#include "MQTTTransceiver.h"
#include "WiFiHandler.h"
#include "OTA.h"
#include "Sleep8266.h"

#include "pin_map.h"

int buzzerFrequency = 784;
bool switchOnStatus = false;

void setup() {
  Serial.begin(115200);  // Debugging only

  setup_wifi();

  showWaterLevelSetup();
  swtchSetup();
  setup_receiver(ReceivePIN);

  mqtt_setup(switchOn,switchOff,"",234);

  switchOnStatus = false;
}

void setup_buzzer() {
  pinMode(buzzerPin, OUTPUT);
}

void showWaterLevelSetup() {
  pinMode(level1, OUTPUT);
  pinMode(level2, OUTPUT);
  pinMode(level3, OUTPUT);
  pinMode(level4, OUTPUT);
  pinMode(level5, OUTPUT);
}

void swtchSetup() {
  pinMode(switchRelay, OUTPUT);
}

void switchEvent(int level) {
  if (level == 0x1F) {
    switchOff();
  } else if (level == 0) {
    switchOn();
  }
}

void switchOff() {
  digitalWrite(switchRelay, LOW);
  noTone(buzzerPin);
  switchOnStatus = false;
}

void switchOn() {
  digitalWrite(switchRelay, HIGH);
  switchOnStatus = true;
}

void updateWaterLevel(int level) {
  digitalWrite(level1, level & 0x01);
  digitalWrite(level2, level & 0x02);
  digitalWrite(level3, level & 0x04);
  digitalWrite(level4, level & 0x08);
  digitalWrite(level5, level & 0x10);
}



long lastLevel = -1;
void loop() {

  wifi_connect();

  long level = receive();

  // if (level != -1) {
  //   Serial.print("Received:");
  //   Serial.println(level);
  // }

  if (lastLevel != level && level != -1) {

    level = level & 0x1F;
    lastLevel = level;
    Serial.println(level);
    updateWaterLevel(level);
    switchEvent(level);
  }

  mqtt_loop();

  if (switchOnStatus) {
    tone(buzzerPin, buzzerFrequency);
  }

  sleep();

}