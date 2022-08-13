void setup() {
  Serial.begin(9600);
  rf_setup();
  reader_setup();
}

void loop() {
  int level = readWaterLevel();
  Serial.println(level);
  char buffer [2];
  itoa(level,buffer,10);
  rf_send(buffer);
  Serial.println(buffer);
  delay(1000);
}