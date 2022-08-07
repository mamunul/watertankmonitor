#define F_CPU 8000000

int outPin = PIN_PC5;
const int interruptPin = 2;

void example() {
}

void setup() {
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
  rf_setup();
  // setup_rf24();
}

void waterLevelChanged() {
}


void blink() {
  digitalWrite(outPin, HIGH);
  delay(1000);
  digitalWrite(outPin, LOW);
  delay(1000);
}

void loop() {
  rf_send();
  // send_rf24();
  blink();
  // blink();
  // sleepNow();          // Call the sleep routine: sleepNow()
  // After_Wakeup_Now();  // do something after wakeup
}