#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver(2000, PIN_PB6, PIN_PB7, PIN_PD5);//rx,tx
void rf_setup() {

  // Serial.begin(9600);  // Debugging only
  driver.init();
}

void rf_send() {
  const char *msg = "abcdefghijklmnopqrstuvwxyz0123456789";

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.print("sending complete:");
  Serial.println(msg);
}