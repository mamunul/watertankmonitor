int level1 = D8;
int level2 = D7;
int level3 = D6;
int level4 = D5;
int level5 = D3;

int switchRelay = D0;

void setup() {
  Serial.begin(115200);  // Debugging only
  showWaterLevelSetup();
  swtchSetup();
  setup_receiver();
  // mqtt_setup();
}

void showWaterLevelSetup() {
  pinMode(level1, OUTPUT);
  pinMode(level2, OUTPUT);
  pinMode(level3, OUTPUT);
  pinMode(level4, OUTPUT);
  pinMode(level5, OUTPUT);
}

void swtchSetup() {
  pinMode(switchRelay, OUTPUT);
}

void switchEvent(int level) {
  if (level & 0x1F)
    digitalWrite(switchRelay, LOW);
  else if (level == 0)
    digitalWrite(switchRelay, HIGH);
}

void updateWaterLevel(int level) {
  digitalWrite(level1, level & 0x01);
  digitalWrite(level2, level & 0x02);
  digitalWrite(level3, level & 0x04);
  digitalWrite(level4, level & 0x08);
  digitalWrite(level5, level & 0x10);
}

void loop() {
  int level = receive();
  if (level != -1) {
    level = level & 0x1F;
    Serial.print("received:");
    Serial.println(level);
    // Serial.println();
    updateWaterLevel(level);
    switchEvent(level);
    // mqtt_loop();
  }
}