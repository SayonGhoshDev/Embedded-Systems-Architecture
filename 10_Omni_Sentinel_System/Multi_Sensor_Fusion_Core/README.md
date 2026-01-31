# 🤖 Project 10: OMNI-SENTINEL (Multi-Sensor Fusion System)

## 🎯 Objective
To engineer a sophisticated **Multi-Sensor Fusion System** that mimics biological senses (Vision, Touch, Hearing, Thermal). This project pushes the NodeMCU to its limits by managing **4 distinct sensors** simultaneously using advanced GPIO allocation and non-blocking logic.

## 🧠 Engineering Logic

### 1. Hybrid GPIO Logic (The "Danger Pin" Hack)
NodeMCU has limited "Safe Pins". To utilize all sensors, we used the Boot Configuration Pins (`D3`, `D4`) safely:
* **Challenge:** Pins `D3` & `D4` must be HIGH during boot, or the board fails to start.
* **Solution:** Used **Active Low Configuration** (Pin -> LED (-) ... (+) -> 3.3V). This acts as a hardware "Pull-Up", keeping the pins HIGH during boot while allowing software control (LOW to turn ON).

### 2. Analog Peak Detection (Sound)
* **Problem:** Digital Sound Sensors (`D0`) are unstable and prone to false positives due to sampling rate mismatch.
* **Solution:** Switched to **Analog Input (`A0`)** with a software-defined **Sampling Window (50ms)**.
* **Algorithm:** The code listens for 50ms, calculates the "Peak-to-Peak" amplitude (Max - Min), and triggers only if the volume exceeds a calibrated threshold (400).

### 3. Sensor Fusion Architecture
The `loop()` function manages four distinct subsystems without blocking the processor:
1.  **Radar (HC-SR04):** Detects proximity (<10cm) -> Triggers Red LED.
2.  **Touch (IR):** Detects physical contact -> Triggers Buzzer.
3.  **Audio (KY-037 Analog):** Detects Claps -> Triggers Green LED.
4.  **Thermal (DHT11):** Monitors Heat (>30°C) -> Triggers Yellow LED.

## 🛠️ Hardware Stack
* **Core:** NodeMCU v3 (ESP8266)
* **Vision:** HC-SR04 Ultrasonic Sensor
* **Touch:** TCRT5000 IR Sensor
* **Audio:** KY-037 Microphone (Analog Mode)
* **Thermal:** DHT11 Temp/Humidity Sensor
* **Indicators:** 3x LEDs (Red, Yellow, Green) & Active Buzzer

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
