int levels[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x5 };
int level_count = 6;
int current_level = -1;
void detector_setup() {
  SFIOR |= 1 << ACME;
  ADCSRA &= ~(1 << ADEN);
  ACSR = (1 << ACBG) | (1 << ACIE);  // ACOMP Interrupt enabled

  set_next_int_level();
}

ISR(ANA_COMP_vect) {
  Serial.print("water level:");
  Serial.println(current_level);
  set_next_int_level();
}

void set_next_int_level() {
  current_level++;
  current_level %= level_count;
  ADMUX &= levels[current_level];
}

void check_water_level() {
}