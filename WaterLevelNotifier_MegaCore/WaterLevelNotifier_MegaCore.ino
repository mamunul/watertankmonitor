#include <RCSwitch.h>

void setup() {
  Serial.begin(9600);
  rf_setup();
  reader_setup();
}

void loop() {
  int level = readWaterLevel();
  level = level & 0x1F;
  if (level == 0) level = 128;
  Serial.println(level);
  rf_send(level);
  delay(1000);
}