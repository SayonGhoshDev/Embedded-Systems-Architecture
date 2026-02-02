# 🚜 Project A.R.E.S.: Propulsion System (L298N Logic)

## 🎯 Objective
To engineer the foundational **Propulsion System** for **Project A.R.E.S. (Autonomous Robotic Exploration System)**. This experiment interfaces the heavy-duty **L298N H-Bridge Driver** with the delicate 3.3V logic of the NodeMCU, ensuring safe and bidirectional motor control with visual feedback.

## 🧠 Engineering Logic

### 1. The "Active Low" Safety Protocol
* **Challenge:** Pins **D3 (GPIO 0)** and **D4 (GPIO 2)** are critical "Boot Configuration Pins". If they are pulled LOW during startup, the NodeMCU enters Flash Mode and fails to boot code.
* **Solution:** We used **Active Low Logic** for the Rear Light connected to D4.
    * **Wiring:** Pin (D4) -> LED Cathode (-) ... Anode (+) -> 3.3V.
    * **Physics:** This configuration acts as a hardware Pull-Up, keeping D4 HIGH during boot (Safe State).
    * **Code:** `digitalWrite(D4, LOW)` is used to turn the LED **ON** (Current Sink), and `HIGH` turns it **OFF**.

### 2. H-Bridge Logic (L298N)
The L298N module serves as the "Muscles" of the A.R.E.S. Rover, enabling bidirectional movement:
* **Forward:** `IN1 = HIGH`, `IN2 = LOW` (Current flows A to B).
* **Backward:** `IN1 = LOW`, `IN2 = HIGH` (Current flows B to A).
* **Brake/Stop:** `IN1 = LOW`, `IN2 = LOW` (No potential difference).

## 🛠️ Hardware Stack
* **Controller:** NodeMCU v3 (ESP8266)
* **Driver:** L298N Dual H-Bridge Motor Driver
* **Actuator:** DC Gear Motor (Bo Motor)
* **Visuals:** * **Headlight:** Yellow LED (Active High)
    * **Rear Light:** Red LED (Active Low on D4)
    * **Indicator:** Green LED (Blinking Logic)

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
