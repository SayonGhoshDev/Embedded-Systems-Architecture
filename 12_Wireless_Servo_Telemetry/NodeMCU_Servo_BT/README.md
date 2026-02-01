# 📡 Wireless Servo Actuation via Bluetooth (HC-05)

## 🎯 Objective
To establish a robust **Wireless Telemetry Link** between an Android terminal and the NodeMCU ESP8266. This experiment serves as the foundational test for the **"Robotic Head/Neck Mechanism"** of Project A.R.E.S., enabling remote directional scanning.

## 🧠 Engineering Logic

### 1. UART Emulation (SoftwareSerial)
* **Challenge:** The NodeMCU uses its primary Hardware UART (TX/RX) for USB communication and programming. Connecting Bluetooth directly to these pins causes upload failures and interference.
* **Solution:** implemented **SoftwareSerial** library to virtualize a secondary Serial Port on GPIO pins **D2 (RX)** and **D3 (TX)**.
* **Benefit:** Allows real-time debugging on the PC monitor *while simultaneously* receiving wireless commands from the phone.

### 2. LIDAR Scanning Simulation
* The system implements an **Auto-Sweep Algorithm** (Command 'S') that smoothly rotates the servo from 0° to 180° and back. 
* In the final rover, an Ultrasonic Sensor will be mounted on this servo to create a **180° Virtual Map** of obstacles, mimicking a LIDAR system.

## 🛠️ Hardware Stack
* **Controller:** NodeMCU v3 (ESP8266)
* **Communication:** HC-05 Bluetooth Module (Classic 2.0)
* **Actuator:** SG90 Micro Servo Motor
* **Power Logic:** Direct 5V (Vin) supply for Motor Torque

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
