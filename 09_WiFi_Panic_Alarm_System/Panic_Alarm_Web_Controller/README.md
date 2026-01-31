# 🚨 WiFi Panic Alarm System (Active High Logic)

## 🎯 Objective
To implement a remote-controlled emergency alert system using the **ESP8266 Web Server**. This project marks the transition from controlling internal components to interfacing with **External Actuators** (LEDs & Active Buzzers) using **Current Source Topology** (Active High).

## 🧠 Engineering Logic

### 1. Active High vs. Active Low
* **Internal LED (Previous Exp):** Used **Active Low** (Current Sink) because the Anode was tied to 3.3V.
* **External Circuit (This Exp):** Uses **Active High** (Current Source).
    * **Wiring:** Pin -> Component (+) -> Resistor -> GND.
    * **Physics:** Setting the Pin to `HIGH` (3.3V) creates a potential difference against GND (0V), allowing current to flow out of the pin to drive the load.

### 2. GPIO & Web Control
The system exposes specific API endpoints that trigger physical voltage changes:
* `http://<IP>/alarm/on` -> Triggers `digitalWrite(D2, HIGH)` -> Activates Piezo Buzzer.
* `http://<IP>/led/on` -> Triggers `digitalWrite(D1, HIGH)` -> Activates Visual Warning.

## 🛠️ Hardware Stack
* **Controller:** NodeMCU v3 (ESP8266)
* **Visual Output:** 5mm Red LED (with 220Ω Resistor)
* **Audio Output:** 5V Active Piezo Buzzer
* **Interface:** WiFi 802.11 b/g/n (HTTP Protocol)

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
