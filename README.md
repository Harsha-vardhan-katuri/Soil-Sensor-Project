# LoRa-Enabled Soil Health Monitoring System using RS485 and ESP32

This project implements a smart agricultural monitoring system that measures multiple soil parameters using an RS485 Modbus-based sensor and transmits the data wirelessly using LoRa technology. The system is built around the ESP32 microcontroller and is designed for deployment in remote field conditions where long-range, low-power communication is essential.

## 🌱 Features

* 📡 Long-range wireless data transmission via LoRa (433 MHz)
* 🦢 Real-time soil data acquisition: Nitrogen (N), Phosphorus (P), Potassium (K), pH, EC, Moisture, and Temperature
* 🔁 RS485 (Modbus RTU) communication between ESP32 and soil sensor
* 🛠️ Efficient and modular firmware structure using Arduino framework
* ⚡ Optimized for low power and outdoor deployments

---

## 🔧 Hardware Components

| Component                | Description                               |
| ------------------------ | ----------------------------------------- |
| ESP32 Dev Module         | Microcontroller for sensor + LoRa control |
| Soil Sensor              | Multi-parameter sensor (Modbus RTU)       |
| LoRa SX1278 Module       | Transceiver for long-range communication  |
| RS485                    | Handles Modbus communication              |
| Jumper wires, Breadboard | Prototyping connections                   |


## ⚙️ Setup Instructions

### 1. Transmitter (ESP32 + RS485 Soil Sensor + LoRa)

* Connect RS485 sensor to ESP32 using UART pins.
* Connect LoRa module via SPI (SCK, MISO, MOSI, CS, RST, DIO0).
* Flash the `transmitter_code` using Arduino IDE or PlatformIO.
* Power up ESP32. Sensor values will be read and transmitted periodically.

### 2. Receiver (ESP32 or LoRa Node)

* Connect LoRa module to a second ESP32 or compatible MCU.
* Flash the `receiver_code` to read incoming LoRa packets and print via Serial Monitor.

---

## 📊 Sample Output

### Transmitter Side

```
Reading Soil and NPK Values...
Nitrogen: 55 mg/kg
Phosphorus: 24 mg/kg
Potassium: 87 mg/kg
Soil Moisture: 31.2 %
Soil Temp: 26.7 °C
EC: 486 µS/cm
pH: 6.8
LoRa packet sent!
```

### Receiver Side

```
Booting Receiver...
LoRa Receiver Ready.
Received: N:55,P:24,K:87,M:31.2,T:26.7,EC:486,pH:6.8
```

---

## 🔐 Future Improvements

* Add SD card logging
* Integrate ThingSpeak or Blynk for cloud monitoring
* Use deep sleep mode for better power efficiency
* Multi-node scheduling for sensor networks

---

## 🧠 Skills & Technologies Used

* Embedded C / Arduino
* RS485 (Modbus RTU)
* LoRa SX1278
* SPI, UART communication
* ESP32 development

---

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---

## 🤝 Acknowledgements

Made with 🌿 for smart farming applications and environmental sensing.
