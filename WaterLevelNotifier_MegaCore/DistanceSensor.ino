#define echoPin PIN_PD4  // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin PIN_PD3  //attach pin D3 Arduino to pin Trig of HC-SR04

void distance_sensor_setup() {
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT);   // Sets the echoPin as an INPUT
}

long measure_distance() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  long distance_cm = duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
  return distance_cm;
}