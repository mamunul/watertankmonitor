#include <avr/sleep.h>
#include <avr/interrupt.h>

void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  // noInterrupts();                                                        // make sure we don't get interrupted before we    sleep
  power_all_disable();                                                   // disables all modules
  sleep_enable();                                                        // enables the sleep bit in the mcucr register
  // attachInterrupt(digitalPinToInterrupt(2), waterLevelChanged, CHANGE);  // wake up on RISING level on D2
  // interrupts();                                                          // interrupts allowed now, next instruction WILL be executed
  sleep_cpu();                                                           // here the device is put to sleep
}  // end of sleepNow

void After_Wakeup_Now() {
  sleep_disable();                                       // first thing after waking from sleep:
  // detachInterrupt(digitalPinToInterrupt(interruptPin));  // stop RISING interrupt on D2
  Serial.println("Back from Sleep");
}