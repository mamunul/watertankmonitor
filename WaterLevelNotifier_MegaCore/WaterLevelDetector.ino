
void reader_setup() {
  enableReadMode();
}

void enableReadMode() {
  DDRC = B00000000;
  PORTC = B00000000;// use pull-down resistor, and vcc to water
}

int readWaterLevel() {
  return PINC;
}