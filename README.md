# 🏛️ Embedded Systems Architecture & AIoT Integration

![Status](https://img.shields.io/badge/Status-Active_Development-success)
![Hardware](https://img.shields.io/badge/Hardware-AVR_%7C_ESP8266-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B_%28Embedded%29-orange)

## 📜 Research Overview
This repository serves as a comprehensive archive of **Low-Level Firmware Architectures** and **Scalable IoT Solutions**. The objective is to document the transition from bare-metal **AVR Register Manipulation** (Arduino) to **Cloud-Native Asynchronous Networking** (ESP8266/NodeMCU).

The focus extends beyond wiring; it emphasizes **Non-Blocking Logic (Finite State Machines)**, **Hardware Interrupt Service Routines (ISRs)**, and **TCP/IP Protocol Stack Implementation**.

---

## 🛠️ Architecture Modules

### 🔹 Phase 1: Bare-Metal Concurrency & Control (AVR)
*Focus: ATmega328P Architecture, Register Logic, and Signal Processing.*
* **Asynchronous Multitasking:** Replacing blocking `delay()` with `millis()` based **Finite State Machines (FSM)**.
* **Hardware Interrupts (ISRs):** Implementing prioritized, real-time event handling for sensors to minimize CPU polling overhead.
* **Pulse Width Modulation (PWM):** Precision duty-cycle manipulation for servo actuators and motor drivers.
* **Sensor Fusion:** Combining Ultrasonic (Sound) and IR (Light) data for robust environmental mapping.

### 🔹 Phase 2: The Internet of Things & Network Layer (ESP8266)
*Focus: 32-bit Xtensa Architecture, WiFi Station Mode, and Web Protocols.*
* **Active Low Architecture:** Implementing Current Sink topologies for 3.3V logic peripherals.
* **TCP/IP Networking:** Configuring NodeMCU as a standalone **HTTP Web Server** handling GET/POST requests.
* **Wireless Telemetry:** Creating a "Zero-Wire" control interface via Local Area Network (LAN).
* **Client-Server Handshake:** Designing API endpoints (Routes) for remote hardware actuation.

---

## 🚀 Capstone Projects (The Masterpieces)

### 🤖 Project A.R.E.S. (Autonomous Robotics & Environmental Sensing)
* **Status:** `In Development`
* **Core Logic:** A self-driving vehicular unit powered by L298N H-Bridge drivers.
* **Features:**
    * Real-time Obstacle Avoidance using Ultrasonic Echolocation.
    * Pathfinding algorithms based on IR Proximity Logic.
    * Autonomous decision-making without human intervention.

### 🏠 Project N.E.X.U.S. (Network Enabled Xtensible Unit for Security)
* **Status:** `Prototype Phase`
* **Core Logic:** A Sentient Home Automation Hub utilizing the IoT Stack.
* **Features:**
    * **Global Control:** Remote appliance switching via Web Dashboard.
    * **Bio-Rhythm Lighting:** Auto-adjustment of lights based on ambient LDR sensor data.
    * **Climate Awareness:** Automated fan control triggered by DHT11 temperature thresholds.
    * **Voice Gateway:** Integration with Google Assistant for hands-free commands.

---
*Maintained by **Sayon Ghosh** | CSE Undergraduate*
