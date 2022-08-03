#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver;
void rf_setup() {

  // Serial.begin(9600);  // Debugging only
  driver.init();
}

void rf_send() {
  const char *msg = "abcdefghijklmnopqrstuvwxyz0123456789";

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
}