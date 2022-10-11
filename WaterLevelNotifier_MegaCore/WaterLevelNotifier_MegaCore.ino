#include <RCSwitch.h>

void setup() {
  // Serial.begin(9600);
  rf_setup();
  sleep_setup();
  distance_sensor_setup();
}
// long distance = 5;
void loop() {
  long distance = measure_distance();
  // distance++;
  // distance %= 250;
  // Serial.println(distance);
  rf_send(distance);
  // delay(1000);
  sleepForOneMinute();
}