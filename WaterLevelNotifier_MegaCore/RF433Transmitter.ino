#include <RH_ASK.h>
#include <SPI.h>
RH_ASK driver(2000, PIN_PB6, PIN_PB7, PIN_PD5);  //rx,tx
void rf_setup() {
  driver.init();
}

void rf_send(char *message) {
  driver.send((uint8_t *)message, strlen(message));
  driver.waitPacketSent();
}