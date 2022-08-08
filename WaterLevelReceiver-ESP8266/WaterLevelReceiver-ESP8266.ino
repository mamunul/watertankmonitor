void setup() {
  Serial.begin(9600);  // Debugging only
  // setup_receiver();
  // setup_receiver_rf24();
  mqtt_setup();
}

void loop() {
  // receive();
  // receive_rf24();
  mqtt_loop();
}