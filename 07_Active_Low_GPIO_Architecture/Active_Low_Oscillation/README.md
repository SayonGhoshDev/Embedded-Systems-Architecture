# ⚡ Active Low GPIO Architecture (ESP8266)

## 🎯 Objective
To validate the **Current Sink Topology** of the 32-bit Tensilica Xtensa Architecture (ESP8266). This project demonstrates the inversion logic required to interface with on-board peripherals, marking the transition from 8-bit AVR (Arduino) Active High logic to 32-bit IoT Active Low logic.

## 🧠 Engineering Logic

### 1. The "Current Sink" Physics
* **Standard Logic (Arduino):** Typically, we send `HIGH` to turn a device ON (Source Current).
* **ESP8266 Logic:** The on-board LED's Anode is permanently tied to the **3.3V Rail**. The GPIO pin acts as the Cathode.
* **Mechanism:** * To turn **ON**, the code writes `LOW` (GND), allowing current to flow into the pin (Sinking).
    * To turn **OFF**, the code writes `HIGH` (3.3V), neutralizing the potential difference (3.3V - 3.3V = 0V).

### 2. Register Mapping (HAL)
* The software uses a Hardware Abstraction Layer (HAL) where board labels (`D4`) map to specific internal registers (`GPIO 02`).
* **Boot Signal:** Pin D4 is also linked to `UART1_TXD`. Upon reset, the LED flashes rapidly, indicating serial data transmission during the bootloader sequence.

## 🛠️ Hardware Stack
* **SoC:** NodeMCU v3 (ESP-12E Module)
* **Processor:** Tensilica Xtensa® 32-bit L106
* **Actuator:** On-board Blue Status LED (Hardwired to GPIO 2)

---
*Developed by **Sayon Ghosh** | CSE Undergraduate Student*
