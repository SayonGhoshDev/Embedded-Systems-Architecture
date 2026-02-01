# ⚡ AC Load Control & Logic Level Synchronization

## 🎯 Objective
To engineer a **Web-Controlled Switching System** for high-voltage AC loads using the **NodeMCU ESP8266**. This experiment solves the critical "Logic Level Mismatch" issue between 3.3V microcontrollers and standard 5V Relay Modules without using external level shifters.

## 🧠 Engineering Logic

### 1. The "Active Low" Logic Clash
* **Problem:** Standard Relay Modules are designed for 5V logic. When a NodeMCU sends a `HIGH` signal (3.3V), the relay sees a potential difference of `5V - 3.3V = 1.7V`. This residual voltage is often enough to keep the optocoupler active, meaning the Relay **never turns OFF**.
* **The "3.3V Hack" Solution:** * Instead of powering the Relay VCC with 5V, we powered it with **3.3V**.
    * **Result:** * NodeMCU HIGH (3.3V) - Relay VCC (3.3V) = **0V Difference** (Relay OFF).
        * NodeMCU LOW (0V) - Relay VCC (3.3V) = **3.3V Difference** (Relay ON).
    * This simple voltage adjustment synchronized the logic levels perfectly without extra transistors.

### 2. Web Server Control
The system hosts a local HTTP server that parses URL commands to toggle the GPIO state, forming the backbone of **Project N.E.X.U.S.** (Home Automation).

## 🛠️ Hardware Stack
* **Controller:** NodeMCU v3 (ESP8266)
* **Actuator:** 1-Channel Relay Module (Active Low)
* **Load:** 220V AC Bulb (Connected via COM/NO ports)
* **Interface:** WiFi 802.11 b/g/n (HTTP Protocol)

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
