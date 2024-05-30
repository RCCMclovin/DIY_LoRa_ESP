#include <SPI.h>
#include <SD.h>
#include <LoRa.h>

//LoRa Pins
#define csPin 3
#define resetPin 1
#define irqPin 2

//SD Pin
#define CS 7

//SPI Interface Pins
#define SCK 4
#define MISO 5
#define MOSI 6



int counter = 0;

void setup() {
  //pinMode(csPin, OUTPUT);
  //pinMode(CS, OUTPUT);
  
  Serial.begin(115200);
  while (!Serial);
  Serial.println("");

  ///*

  //digitalWrite(CS,HIGH);
  //digitalWrite(csPin,LOW);

  Serial.print("Inicializando o cartão SD...");
  SPI.begin(SCK,MISO,MOSI,CS);
  if (!SD.begin(CS)) {
    Serial.println("Falha, verifique se o cartão está presente.");
    //Early return
    return;
  }
  Serial.println("Cartão inicializado.");

  //digitalWrite(CS,LOW);
  //digitalWrite(csPin,HIGH);

  //*/

  ///*
  Serial.println("LoRa Sender");
  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  //Set LoRa Params
  LoRa.setSpreadingFactor(9);
  LoRa.setCodingRate4(5);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setPreambleLength(8);
  LoRa.setTxPower(20, PA_OUTPUT_PA_BOOST_PIN);

  //*/

}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  ///*

  //digitalWrite(CS,HIGH);
  //digitalWrite(csPin, LOW);

  File dataFile = SD.open("/LOG.txt", FILE_APPEND);
  if (dataFile) { //Verify if file was oppened correctly
    Serial.println("O arquivo foi aberto com sucesso.");
      dataFile.println(counter);
      dataFile.close();
  }
  else {
    Serial.println("Falha ao abrir o arquivo LOG.txt");
  }

  //digitalWrite(CS,LOW);
  //digitalWrite(csPin, HIGH);

  //*/

  ///*
  // send packet
  LoRa.beginPacket();
  Serial.print(".");
  LoRa.print("hello ");
  LoRa.print(counter);
  Serial.print(".");
  LoRa.endPacket();
  Serial.println(".");

  //*/
  counter++;

  delay(2000);
}
