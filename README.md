# 🏛️ Embedded Systems Architecture & AIoT Integration

![Status](https://img.shields.io/badge/Status-Research_Sprint_Completed-success)
![Hardware](https://img.shields.io/badge/Hardware-AVR_%7C_ESP8266-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B_%28Embedded%29-orange)

## 📜 Research Overview
This repository serves as a comprehensive archive of **Low-Level Firmware Architectures** and **Scalable IoT Solutions**. The objective is to document the 15-day R&D transition from bare-metal **AVR Register Manipulation** (Arduino) to **Cloud-Native Asynchronous Networking** (ESP8266/NodeMCU).

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

## 🚀 Capstone Project (The Masterpiece)

### 🤖 [Project A.R.E.S. (Autonomous Robotic Exploration System)](./Project_A.R.E.S_Rover)
* **Status:** `Completed`
* **Core Logic:** A Hybrid Control Rover featuring Sensor Fusion and Real-Time Telemetry.
* **Key Innovations:**
    * **Hybrid Architecture:** Seamless switching between **Manual Bluetooth Control** and **Autonomous Navigation**.
    * **Smart-Turn Heuristic:** Deterministic decision tree for obstacle avoidance (Look-Compare-Turn).
    * **Adaptive Signal Processing:** Boot-time auto-calibration for ambient noise cancellation.
    * **Safety Protocols:** Active Low logic for functional brake lights and cliff detection.

*(Click the project title to view the full Documentation, Source Code, and Circuit Analysis)*

---

## 🔮 Future Roadmap (Upcoming Integrations)
The following architectures are scheduled for the next development cycle:
* **Project N.E.X.U.S.:** Complete deployment of the IoT Home Automation Hub.
* **Cloud Telemetry:** Integration of ESP8266 for AWS/Firebase data logging.

---
*Maintained by **Sayon Ghosh** | CSE Undergraduate*
