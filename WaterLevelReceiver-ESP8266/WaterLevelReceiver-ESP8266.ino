extern "C" {
#include "user_interface.h"
}

int level1 = D8;
int level2 = D7;
int level3 = D6;
int level4 = D5;
int level5 = D3;

int switchRelay = D0;
int buzzerPin = D1;  //GPIO_ID_PIN(1);
int buzzerFrequency = 784;
bool switchOnStatus = false;
void setup() {
  Serial.begin(115200);  // Debugging only
  setup_wifi();
  showWaterLevelSetup();
  swtchSetup();
  setup_receiver();
  mqtt_setup();
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

void sleep() {
  wifi_fpm_set_sleep_type(LIGHT_SLEEP_T);
  wifi_fpm_open();

  // register one or more wake-up interrupts
  gpio_pin_wakeup_enable(D4, GPIO_PIN_INTR_HILEVEL);
  //gpio_pin_wakeup_enable(D3, GPIO_PIN_INTR_LOLEVEL);
  // ...

  // function for clearing all previously set wake interrupts:
  //gpio_pin_wakeup_disable();

  // optionally, can register a callback function using
  //wifi_fpm_set_wakeup_cb(function_name);

  // actually enter light sleep:
  // the special timeout value of 0xFFFFFFF triggers indefinite
  // light sleep (until any of the GPIO interrupts above is triggered)
  wifi_fpm_do_sleep(0xFFFFFFF);
  // the CPU will only enter light sleep on the next idle cycle, which
  // can be triggered by a short delay()
  delay(1000);
}

int lastLevel = -1;
void loop() {
  wifi_connect();
  int level = receive();

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