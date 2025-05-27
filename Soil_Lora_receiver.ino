#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK  18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_CS   4
#define LORA_RST  14
#define LORA_IRQ  2

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Booting Receiver...");

  pinMode(LORA_RST, OUTPUT);
  digitalWrite(LORA_RST, LOW);
  delay(10);
  digitalWrite(LORA_RST, HIGH);
  delay(10);

  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed.");
    while (1);
  }

  Serial.println("LoRa Receiver Ready.");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Received: ");
    while (LoRa.available()) {
      char c = LoRa.read();
      Serial.print(c);
    }
    Serial.println();
  }
  delay(100);
}
