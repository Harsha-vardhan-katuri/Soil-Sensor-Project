# Real-Time Soil Quality Monitoring System  

## 📌 Introduction  
Soil analysis is crucial for optimizing agricultural productivity and ensuring sustainable farming practices. Accurate monitoring of key soil parameters enables informed decision-making for better crop management.  

This project implements a **7-in-1 Soil Sensor** using two different methods:  
- **Method 1:** RS485-to-USB converter with **Cool Term** software.  
- **Method 2:** RS485-to-TTL converter with **Arduino Uno** and **Arduino IDE**.  

## 🎯 Objective  
The primary goals of this project are to:  
- Implement and evaluate two different methods for soil quality measurement.  
- Analyze key soil parameters such as **pH, Electrical Conductivity (EC), NPK (Nitrogen, Phosphorus, Potassium), Temperature, and Moisture**.  
- Compare the accuracy, efficiency, and response time of both methods to determine the most effective approach.  
- Identify the best method for **real-time agricultural applications**.  

## 🛠️ Hardware Requirements  
- **7-in-1 Soil Sensor** (Measures pH, EC, NPK, Temperature, and Moisture)  
- **RS485-to-USB Converter** (For direct PC communication)  
- **RS485-to-TTL Converter** (For microcontroller interfacing)  
- **Arduino Uno** (Microcontroller for Method 2)  
- **UTP1306 Power Supply** (12V-24V input for the sensor)  
- **Multimeter** (For testing connections)  
- **Soil Sample** (For testing)  

## 💻 Software Requirements  
- **Arduino IDE** (For programming and serial monitoring)  
- **Cool Term Software** (For RS485 to USB communication)  

## 📋 Methodology  

### 🔹 Method 1: RS485 to USB with Cool Term Software  
- The **7-in-1 soil sensor** is connected to an **RS485-to-USB converter**.  
- The converter allows **direct data transmission** to a computer.  
- **Cool Term software** is used to **send query packets** and retrieve sensor data.  
- No microcontroller is required.  

### 🔹 Method 2: RS485 to TTL with Arduino Uno and Arduino IDE  
- The **7-in-1 soil sensor** is connected to an **RS485-to-TTL converter**.  
- The **TTL converter** interfaces with the **Arduino Uno**.  
- The **Arduino Uno** processes the sensor data and sends it to the **Arduino IDE serial monitor** for real-time display.  
- Suitable for **embedded systems and IoT applications**.  


## ⚙️ Working Principles  

### ✅ Method 1 (RS485 to USB with Cool Term)  
1. Power the **7-in-1 soil sensor** with a **12V DC power supply**.  
2. Connect the **RS485 A & B terminals** to the **RS485-to-USB converter**.  
3. Plug the **USB converter** into the **computer**.  
4. Open **Cool Term software**, set the **baud rate and COM port**.  
5. Send a **hexadecimal query command** to request data from the sensor.  
6. The sensor **sends back** real-time data for analysis.  

### ✅ Method 2 (RS485 to TTL with Arduino Uno)  
1. Power the **7-in-1 soil sensor** using a **12V DC power supply**.  
2. Connect the **RS485 A & B terminals** to the **RS485-to-TTL module**.  
3. Connect the **TTL module** to the **Arduino Uno** as follows:  
   - **RX (Receive) → Arduino Digital Pin**  
   - **TX (Transmit) → Arduino Digital Pin**  
4. Upload the **RS485 communication code** to the Arduino.  
5. The **Arduino requests** data from the sensor.  
6. The **sensor sends the response**, which is displayed on the **Arduino IDE Serial Monitor**.  

## 📊 Results  

| Parameter       | Method 1 (RS485-USB) | Method 2 (RS485-TTL) |
|----------------|---------------------|---------------------|
| **Nitrogen**   | 38 mg/kg             | 37.83 mg/kg         |
| **Phosphorus** | 53 mg/kg             | 53 mg/kg            |
| **Potassium**  | 106.73 mg/kg         | 106 mg/kg           |
| **pH**         | 7                    | 6.4                 |
| **Temperature**| 25.2°C               | 25.2°C              |
| **Moisture**   | 11.6%                | 10.8%               |
| **EC**         | 536 µS/cm            | 532 µS/cm           |

## ✅ Conclusion  

This project successfully evaluated the **7-in-1 soil sensor** using two methods for **measuring soil quality parameters**.  

- **Method 1 (RS485 to USB)** provides **higher accuracy** due to **direct data retrieval**.  
- **Method 2 (RS485 to TTL with Arduino Uno)** offers **better flexibility** for **embedded systems** and **IoT applications**.  

## 📌 Pros & Cons  

### ✅ Method 1 (RS485 to USB with Cool Term)  
✔ **High Accuracy** – Direct data retrieval ensures minimal noise.  
✔ **Easy Setup** – No microcontroller required.  
✔ **Real-Time Monitoring** – Instant data observation.  
❌ **Requires Manual Data Decoding** – Data is in **hexadecimal** format.  
❌ **Limited Portability** – Requires a **PC connection**.  

### ✅ Method 2 (RS485 to TTL with Arduino Uno)  
✔ **Embedded System Integration** – Works with **IoT & automation systems**.  
✔ **Automatic Data Decoding** – Directly displayed in **human-readable format**.  
✔ **Scalability** – Can support **multiple sensors**.  
❌ **Lower Accuracy** – Possible **signal interference**.  
❌ **Requires Additional Programming** – Needs **firmware development**.   

## 📝 Author  
**Harsha Vardhan Katuri**  

## 🔗 License  
This project is licensed under the **MIT License**.  

---


