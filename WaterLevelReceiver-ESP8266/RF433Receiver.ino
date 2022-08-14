#include <RH_ASK.h>
#ifdef RH_HAVE_HARDWARE_SPI
#include <SPI.h>  // Not actually used but needed to compile
#endif

// RH_ASK driver;
RH_ASK driver(2000, D4, D2, D1);  // ESP8266 or ESP32: do not use pin 11 or 2
/// RH_ASK driver(2000, 2, 4, 5);
/// \endcode
/// Which will initialise the driver at 2000 bps, recieve on GPIO2, transmit on GPIO4, PTT on GPIO5.
/// Caution: on the tronixlabs breakout board, pins 4 and 5 may be labelled vice-versa.
#define INT2POINTER(a) ((char*)(intptr_t)(a))

void setup_receiver() {
  driver.init();
}

int receive() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen))  // Non-blocking
  {
    int level = String((char *)buf).toInt();
    return level;
  } else {
    return -1;
  }
}