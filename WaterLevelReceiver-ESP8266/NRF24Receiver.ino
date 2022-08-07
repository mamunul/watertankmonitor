//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(D4, D2);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

void setup_receiver_rf24() {
  // while (!Serial);
  // Serial.begin(9600);

  rf24_datarate_e speed = RF24_250KBPS;

  if (!radio.begin()) { Serial.println("radio hardware not responding!"); }
  //set the address
  radio.openReadingPipe(0, address);
  radio.setChannel(110);
  radio.setDataRate(speed);
  radio.setPALevel(RF24_PA_MIN);
  //Set module as receiver
  radio.startListening();
  delay(1000);
}

void receive_rf24() {
  //Read the data if available in buffer

  // Serial.print("channel:");
  // Serial.print(radio.getChannel());
  // Serial.println();
  // Serial.print("dataRate:");
  // Serial.print(radio.getDataRate());
  // Serial.println();
  if (radio.available()) {
    char text[32] = { 0 };
    radio.read(&text, sizeof(text));
    Serial.print("received:");
    Serial.println(text);
  } else {
    Serial.println("not available");
  }
}