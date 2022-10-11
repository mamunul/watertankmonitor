// #include <RH_ASK.h>
// #include <SPI.h>
// RH_ASK driver(2000, PIN_PB6, PIN_PB7, PIN_PD5);  //rx,tx
RCSwitch mySwitch = RCSwitch();
void rf_setup() {
  // driver.init();
  // Transmitter is connected to Arduino Pin #10
  mySwitch.enableTransmit(PIN_PB0);

  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);

  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
}

void rf_send(long message) {
  mySwitch.send(message, 16);
  delay(100);
  // driver.send((uint8_t *)message, strlen(message));
  // driver.waitPacketSent();
}