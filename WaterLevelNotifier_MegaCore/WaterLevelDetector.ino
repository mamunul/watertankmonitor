
void detector_setup() {
  enableReadMode();
  Serial.println("setup complete");
}

void enableReadMode() {
  DDRC = B00000000;
  PORTC = B00000000;// use pull-down resistor, and vcc to water
}

void readAllPins() {
  int level = PINC;
  Serial.println(level, BIN);
}

void check_water_level() {
  readAllPins();
  delay(1000);
}