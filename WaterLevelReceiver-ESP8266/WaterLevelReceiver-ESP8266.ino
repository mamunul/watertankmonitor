void setup() {
  Serial.begin(9600);  // Debugging only
  setup_receiver();
}

void loop() {
  receive();
}