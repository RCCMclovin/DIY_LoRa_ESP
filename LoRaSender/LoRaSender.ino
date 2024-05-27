#include <SPI.h>
#include <LoRa.h>

//LoRa Pins
#define csPin 15
#define resetPin D1
#define irqPin D0



//SPI Interface Pins
#define SCK D5
#define MISO D6
#define MOSI D7



int counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");
  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  //Set LoRa Params
  LoRa.setSpreadingFactor(7);
  LoRa.setCodingRate4(5);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setPreambleLength(8);
  LoRa.setTxPower(20, PA_OUTPUT_PA_BOOST_PIN);

}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();

  LoRa.print("hello ");
  LoRa.print(counter);

  LoRa.endPacket();

  counter++;

  delay(2000);
}
