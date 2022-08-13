int levels[] = { 0x00, 0x01, 0x02, 0x03, 0x04 };
int level_count = 1;
int current_level = 0;
int lastLevel = 0;
void enableComparator() {
  SFIOR |= 1 << ACME;
  ADCSRA &= ~(1 << ADEN);
}

void disableComparator() {
  SFIOR &= ~(1 << ACME);
  ADCSRA |= (1 << ADEN);
}

void enableComparatorInterrupt() {
  ACSR = (1 << ACBG) | (1 << ACIE);  // ACOMP Interrupt enabled
}

ISR(ANA_COMP_vect) {
  disableComparator();
  cli();
  Serial.print("water level:");
  Serial.println(current_level);
  delay(1000);
  enableComparator();
  set_next_int_level();
  sei();
}

void set_next_int_level() {
  ADMUX &= levels[current_level];
  lastLevel = current_level;
  current_level++;
  current_level %= level_count;
}