
void setup() {
  Serial.begin(9600);
  detector_setup();
}


void blink(int outPin) {
  digitalWrite(outPin, HIGH);
  delay(1000);
  digitalWrite(outPin, LOW);
  delay(1000);
}

void loop() {
  check_water_level();
}