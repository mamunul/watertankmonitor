#include <RCSwitch.h>

void setup() {
  Serial.begin(9600);
  rf_setup();
  reader_setup();
}

void loop() {
  long distance = measure_distance();
  Serial.println(distance);
  rf_send(distance);
  delay(1000);
}