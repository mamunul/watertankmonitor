#define F_CPU 8000000
#include <avr/sleep.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <avr/interrupt.h>

int outPin = PIN_PD6;
const int interruptPin = 2;
// RH_ASK driver;
RH_ASK driver;  // (20, 3, 4, 0);
void example() {
}

void rf_setup() {
  pinMode(outPin, OUTPUT);
  // Serial.begin(9600);  // Debugging only
  driver.init();
}

void rf_send() {
  const char *msg = "abcdefghijklmnopqrstuvwxyz0123456789";

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
}


void setup() {
  // put your setup code here, to run once:
  rf_setup();
}


void waterLevelChanged() {
}


void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  noInterrupts();                                                        // make sure we don't get interrupted before we    sleep
  power_all_disable();                                                   // disables all modules
  sleep_enable();                                                        // enables the sleep bit in the mcucr register
  attachInterrupt(digitalPinToInterrupt(2), waterLevelChanged, CHANGE);  // wake up on RISING level on D2
  interrupts();                                                          // interrupts allowed now, next instruction WILL be executed
  sleep_cpu();                                                           // here the device is put to sleep
}  // end of sleepNow

void After_Wakeup_Now() {
  sleep_disable();                                       // first thing after waking from sleep:
  detachInterrupt(digitalPinToInterrupt(interruptPin));  // stop RISING interrupt on D2
  Serial.println("Back from Sleep");
}

void blink() {
  digitalWrite(outPin, HIGH);
  delay(1000);
  digitalWrite(outPin, LOW);
  delay(1000);
}

void loop() {
  rf_send();
  blink();
  // blink();
  // sleepNow();          // Call the sleep routine: sleepNow()
  // After_Wakeup_Now();  // do something after wakeup
}