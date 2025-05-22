#include <Wire.h>
#include <SoftwareSerial.h>

// RS485 Modbus control pins
#define RE 10   
#define DE 9  

const uint8_t nitrogenRequest[]  = {0x01, 0x03, 0x00, 0x1E, 0x00, 0x01, 0xE4, 0x0C};
const uint8_t phosphorusRequest[] = {0x01, 0x03, 0x00, 0x1F, 0x00, 0x01, 0xB5, 0xCC};
const uint8_t potassiumRequest[]  = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xC0};
const uint8_t moistureRequest[]  = {0x01, 0x03, 0x00, 0x12, 0x00, 0x01, 0x24, 0x0F};
const uint8_t tempRequest[]      = {0x01, 0x03, 0x00, 0x13, 0x00, 0x01, 0x75, 0xCF};
const uint8_t ecRequest[]        = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xCE};
const uint8_t pHRequest[]        = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};

byte response[7];  // Buffer for Modbus response
SoftwareSerial mod(3, 4); // RS485 communication (R0=3, DI=4)

void setup() {
    Serial.begin(9600);
    mod.begin(9600);

    pinMode(RE, OUTPUT);
    pinMode(DE, OUTPUT);
    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);

    Serial.println("NPK & Soil Sensor Ready...");
    delay(2000);
}

void loop() {
    Serial.println("\nReading Soil and NPK Values...");
    
    byte nitrogen    = readModbus(nitrogenRequest, "Nitrogen");
    byte phosphorus  = readModbus(phosphorusRequest, "Phosphorus");
    byte potassium   = readModbus(potassiumRequest, "Potassium");
    uint16_t moisture    = readModbus16(moistureRequest, "Soil Moisture");
    uint16_t temperature = readModbus16(tempRequest, "Soil Temperature");
    uint16_t ec          = readModbus16(ecRequest, "Electrical Conductivity");
    uint16_t pH          = readModbus16(pHRequest, "Soil pH");

    Serial.println("\nProcessed Sensor Data:");
    Serial.print("Nitrogen: ");   Serial.print(nitrogen);   Serial.println(" mg/kg");
    Serial.print("Phosphorus: "); Serial.print(phosphorus); Serial.println(" mg/kg");
    Serial.print("Potassium: ");  Serial.print(potassium);  Serial.println(" mg/kg");
    Serial.print("Soil Moisture: ");  Serial.print(moisture / 10.0);  Serial.println(" %");
    Serial.print("Soil Temperature: "); Serial.print(temperature / 10.0); Serial.println(" °C");
    Serial.print("Electrical Conductivity: "); Serial.print(ec); Serial.println(" µS/cm");
    Serial.print("Soil pH: "); Serial.println(pH / 100.0);  

    delay(500);
}

// Function to read Modbus data (single byte response)
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
            Serial.print("Error: Response Timeout for ");
            Serial.println(paramName);
            return 0;
        }
    }

    Serial.print(paramName);
    Serial.print(" Raw Data: ");
    for (int i = 0; i < 7; i++) {
        response[i] = mod.read();
        Serial.print("0x");
        if (response[i] < 16) Serial.print("0"); // Formatting for single-digit hex values
        Serial.print(response[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    return response[4]; // Extract single-byte NPK value
}

// Function to read 16-bit Modbus data (combining two bytes)
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
            Serial.print("Error: Response Timeout for ");
            Serial.println(paramName);
            return 0;
        }
    }

    Serial.print(paramName);
    Serial.print(" Raw Data: ");
    for (int i = 0; i < 7; i++) {
        response[i] = mod.read();
        Serial.print("0x");
        if (response[i] < 16) Serial.print("0");
        Serial.print(response[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    return (response[3] << 8) | response[4]; // Combine high and low byte
}
