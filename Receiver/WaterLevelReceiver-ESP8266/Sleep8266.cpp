#include "Sleep8266.h"

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