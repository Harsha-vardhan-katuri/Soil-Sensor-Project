#include <Wire.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <LoRa.h>

// RS485 Modbus control pins
#define RE 22  
#define DE 23  

// LoRa module pins
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 2

const uint8_t nitrogenRequest[]  = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};
const uint8_t phosphorusRequest[] = {0x01, 0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC};
const uint8_t potassiumRequest[]  = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0};
const uint8_t moistureRequest[]  = {0x01, 0x03, 0x00, 0x12, 0x00, 0x01, 0x24, 0x0F};
const uint8_t tempRequest[]      = {0x01, 0x03, 0x00, 0x13, 0x00, 0x01, 0x75, 0xCF};
const uint8_t ecRequest[]        = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xCE};
const uint8_t pHRequest[]        = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};

byte response[7];  
HardwareSerial mod(1); // RX/TX: 16/17

void setup() {
    Serial.begin(9600);
    mod.begin(9600, SERIAL_8N1, 16, 17);

    pinMode(RE, OUTPUT);
    pinMode(DE, OUTPUT);
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);

    // LoRa Setup
    SPI.begin(26, 19, 21, LORA_SS); // SCK, MISO, MOSI, SS
    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

    if (!LoRa.begin(433E6)) {
        Serial.println("LoRa init failed. Check connections.");
        while (1);
    }
    Serial.println("LoRa init succeeded.");

    Serial.println("NPK & Soil Sensor Ready...");
    delay(500);
}

void loop() {
    Serial.println("\nReading Soil and NPK Values...");

    byte nitrogen = readModbus(nitrogenRequest, "Nitrogen");
    byte phosphorus = readModbus(phosphorusRequest, "Phosphorus");
    byte potassium = readModbus(potassiumRequest, "Potassium");
    uint16_t moisture = readModbus16(moistureRequest, "Soil Moisture");
    uint16_t temperature = readModbus16(tempRequest, "Soil Temperature");
    uint16_t ec = readModbus16(ecRequest, "Electrical Conductivity");
    uint16_t pH = readModbus16(pHRequest, "Soil pH");

    Serial.println("\nProcessed Sensor Data:");
    Serial.print("Nitrogen: ");   Serial.print(nitrogen);   Serial.println(" mg/kg");
    Serial.print("Phosphorus: "); Serial.print(phosphorus); Serial.println(" mg/kg");
    Serial.print("Potassium: ");  Serial.print(potassium);  Serial.println(" mg/kg");
    Serial.print("Soil Moisture: "); Serial.print(moisture / 10.0); Serial.println(" %");
    Serial.print("Soil Temp: "); Serial.print(temperature / 10.0); Serial.println(" °C");
    Serial.print("EC: "); Serial.print(ec); Serial.println(" µS/cm");
    Serial.print("pH: "); Serial.println(pH / 100.0);  

    // Format data string
    String data = "N:" + String(nitrogen) + ",P:" + String(phosphorus) + ",K:" + String(potassium);
    data += ",M:" + String(moisture / 10.0) + ",T:" + String(temperature / 10.0);
    data += ",EC:" + String(ec) + ",pH:" + String(pH / 100.0);

    // Send via LoRa
    LoRa.beginPacket();
    LoRa.print(data);
    LoRa.endPacket();
    Serial.println("LoRa packet sent!");

    delay(50);
}

byte readModbus(const uint8_t *command, const char *paramName) {
    digitalWrite(DE, HIGH);  
    digitalWrite(RE, HIGH);
    delay(10);

    mod.write(command, 8);
    mod.flush();

    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);

    unsigned long startTime = millis();
    while (mod.available() < 7) {
        if (millis() - startTime > 100) {
            Serial.print("Timeout for ");
            Serial.println(paramName);
            return 0;
        }
    }

    for (int i = 0; i < 7; i++) response[i] = mod.read();
    return response[4];
}

uint16_t readModbus16(const uint8_t *command, const char *paramName) {
    digitalWrite(DE, HIGH);  
    digitalWrite(RE, HIGH);
    delay(10);

    mod.write(command, 8);
    mod.flush();

    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);

    unsigned long startTime = millis();
    while (mod.available() < 7) {
        if (millis() - startTime > 100) {
            Serial.print("Timeout for ");
            Serial.println(paramName);
            return 0;
        }
    }

    for (int i = 0; i < 7; i++) response[i] = mod.read();
    return (response[3] << 8) | response[4];
}
