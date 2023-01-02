#include "RF433Receiver.h"

RCSwitch mySwitch = RCSwitch();

// RH_ASK driver(2000, D4, D2, D1);  // ESP8266 or ESP32: do not use pin 11 or 2
// #define INT2POINTER(a) ((char*)(intptr_t)(a))

void setup_receiver() {
  // driver.init();
  mySwitch.enableReceive(D4);
}

long receive() {
  if (mySwitch.available()) {
    long level = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
    return level;
  } else {
    return -1;
  }
}