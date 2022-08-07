//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(PB0, PB1);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup_rf24() {
  rf24_datarate_e speed = RF24_250KBPS;

  if (!radio.begin()) {
    Serial.println("radio hardware not responding!");
  }

  //set the address
  radio.openWritingPipe(address);
  radio.setChannel(110);
  radio.setDataRate(speed);
  radio.setPALevel(RF24_PA_MIN);

  //Set module as transmitter
  radio.stopListening();
  delay(1000);
}
void send_rf24() {
  //Send message to receiver
  const char text[] = "Hello World";
  bool status = radio.write(&text, sizeof(text));
  Serial.println(status);
  delay(1000);
}