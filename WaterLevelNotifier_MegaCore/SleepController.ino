#include <avr/sleep.h>
#include <avr/interrupt.h>

ISR(TIMER2_OVF_vect) {
  // sleep_disable();
}

void sleep_setup() {
  ASSR |= 1 << AS2;     // bit_set(ASSR, AS2);                                 // Enable asynchronous mode
  TIMSK |= 1 << TOIE2;  //bit_set(TIMSK, TOIE2);                              //Timer/Counter2 Overflow Interrupt Enable
  TIFR |= 1 << TOV2;    //bit_set(TIFR, TOV2);                                //Clear TOV2

  TCNT2 = 0;                                          //Init Timer Count 2
  TCCR2 = ((1 << CS22) | (1 << CS21) | (1 << CS20));  // Timer Clock = system clock / 1024
  // TCCR2 = (1 << CS20);  // Timer Clock = system clock ;3.5 seconds interval with 455 crystal without capacitors
  // TCCR2 = (1 << CS22);  // Timer Clock = system clock / 64
  sei();  //enable_interrupts() <=> bit_set(SREG,7);
}

void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);  // sleep mode is set here
  sleep_enable();

  sleep_mode();     // here the device is actually put to sleep!!
                    // THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
  sleep_disable();  // first thing after waking from sleep:
}

void sleepForOneMinute() {
  for (int i = 0; i < 100; i++)
    sleepNow();
}